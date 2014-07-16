/*
 * file.h
 *
 *  Created on: 2013-3-20
 *      Author: xul
 */

#ifndef _EX_FILE_H_
#define _EX_FILE_H_


#include <string>
#include "base/sy_types.h"

struct FSOperations;

#ifndef FILE_INFO_DEFINED
/// \struct FileInfo
/// \brief 文件信息结构
struct FileInfo
{
	char	name[MAX_PATH];///< 文件名
	uint	attrib;			///< 文件属性
	uint64	time_create;	///< 文件创建时间
	uint64	time_access;	///< 文件访问时间
	uint64	time_write;		///< 文件修改时间
	uint64	size;			///< 文件大小
};
#define FILE_INFO_DEFINED
#endif


struct FileInternal;

/// \class CFile
/// \brief 文件服务封装
class CFile
{
public:

	/// 文件打开标志
	enum OpenFlags {
		modeRead =         (int) 0x00000, ///< 为读打开一个文件，如果文件不存在或无法打开，Open调用失败。
		modeWrite =        (int) 0x00001, ///< 为写创建一个空文件，如果文件存在，其内容将被销毁。
		modeReadWrite =    (int) 0x00002, ///< 为读写打开一个文件，如果文件不存在或无法打开，Open调用失败。
		shareCompat =      (int) 0x00000,
		shareExclusive =   (int) 0x00010,
		shareDenyWrite =   (int) 0x00020,
		shareDenyRead =    (int) 0x00030,
		shareDenyNone =    (int) 0x00040,
		modeNoInherit =    (int) 0x00080,
		modeCreate =       (int) 0x01000, ///< 如果文件不存在，自动创建文件，和modeReadWrite配合使用。
		modeNoTruncate =   (int) 0x02000, ///< 和modeCreate一起使用，如果要创建的文件已经存在，原来的内容保留。
		typeText =         (int) 0x04000, // typeText and typeBinary are
		typeBinary =       (int) 0x08000, // used in derived classes only
		osNoBuffer =       (int) 0x10000, ///< 上层处理缓冲，此时读写的偏移和长度都需要按页面大小对齐。
		osWriteThrough =   (int) 0x20000,
		osRandomAccess =   (int) 0x40000,
		osSequentialScan = (int) 0x80000,
	};

	/// 文件属性
	enum Attribute {
		normal =    0x00,
		readOnly =  0x01,
		hidden =    0x02,
		system =    0x04,
		volume =    0x08,
		directory = 0x10,
		archive =   0x20
	};

	/// 文件定位参考位置
	enum SeekPosition
	{
		begin = 0x0,
		current = 0x1,
		end = 0x2
	};

	/// 文件访问方式
	enum AccessMode
	{
		accessExist = 0,
		accessWrite = 2,
		accessRead = 4,
		accessReadWrite = 6,
	};

	/// 构造函数。
	CFile();

	/// 析构函数。如果数据缓冲还有效，会被释放。
	virtual ~CFile();

	/// 打开文件。打开后文件指针偏移在0处，而以modeAppend标志打开的文件文件指针在文件末尾。
	/// \param [in] pFileName 文件名。
	/// \param [in] dwFlags 打开标志，默认为modeReadWrite。
	/// \retval true  打开成功
	/// \retval false  打开失败，文件不存在或无法打开。
	virtual bool Open(const char* pFileName, unsigned int dwFlags = modeReadWrite);

	/// 关闭文件。
	virtual void Close();

	/// 装载数据，申请和文件长度一样大小的缓冲，将文件内容读到该缓冲，返回缓冲指针。
	/// 和UnLoad函数一起提供方便
	/// \param [in] pFileName 文件名。
	/// \retval NULL  装载失败
	/// \retval !NULL  数据缓冲指针。
	unsigned char * Load(const char* pFileName);

	/// 释放数据缓冲
	void UnLoad();

	/// 读文件数据。读操作后文件指针自动累加。
	/// \param [out] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 要读出的字节数
	/// \retval >0  读出的字节数
	/// \retval <=0 读失败
	virtual unsigned int Read(void *pBuffer, unsigned int dwCount);

	/// 写文件数据。读操作后文件指针自动累加。
	/// \param [out] pBuffer 数据缓冲的指针。
	/// \param [in] dwCount 要写入的字节数
	/// \retval >0  写入的字节数
	/// \retval <=0 写失败
	virtual unsigned int Write(void *pBuffer, unsigned int dwCount);

	/// 同步文件底层缓冲，在写操作后调用，确保写入的数据已经传给操作系统。
	virtual void Flush();

	/// 文件定位。
	/// \param [in] lOff 偏移量，字节为单位。
	/// \param [in] nFrom 偏移相对位置，最后得到的偏移为lOff+nFrom。
	/// \return 偏移后文件的指针位置。
	virtual unsigned int Seek(long lOff, unsigned int nFrom);

	/// 返回当前的文件指针位置
	virtual unsigned int GetPosition();

	/// 返回文件长度
	virtual unsigned int GetLength();

	/// 从文本文件当前偏移处读取一行字符串。读操作后文件指针自动累加。
	/// \param [out] s 数据缓冲。
	/// \param [in] size 需要读取的字符串长度。
	/// \retval NULL  读取失败
	/// \retval !NULL  字符串指针。
	virtual char * Gets(char *s, int size);

	/// 从文本文件当前偏移处写入一行字符串。写操作后文件指针自动累加。
	/// \param [in] s 数据缓冲。
	/// \return  实际写入字符串长度。
	virtual int Puts(const char *s);

	/// 判断文件是否打开
	virtual bool IsOpened();

	/// 重命名文件
	/// \param oldName 旧的文件名
	/// \param oldName 新的文件名
	static bool Rename(const char* oldName, const char* newName);

	/// 删除文件
	/// \param fileName 文件名
	static bool Remove(const char* fileName);

	/// 创建目录
	/// \param 目录名
	static bool MakeDirectory(const char* dirName);

	/// 删除目录
	/// \param 目录名
	static bool RemoveDirectory(const char* dirName);

	/// 文件系统统计
	/// \param path 任意路径，不一定是分区根目录。
	/// \param userFreeBytes 目录所在文件系统分配给该用户的剩余空间字节数
	/// \param totalBytes 目录所在文件系统总的字节数
	/// \param totalFreeBytes 目录所在文件系统总的剩余空间字节数，如果使用了硬盘
	///        空间配额，userFreeBytes可能会比totalFreeBytes小
	static bool StatFS(const char* path,
		uint64* userFreeBytes,
		uint64* totalBytes,
		uint64* totalFreeBytes);

	/// 判断文件或目录访问权限
	/// \param path 文件或目录的路径。
	/// \param mode 访问权限，\see AccessMode
	/// \return 是否有mode指定的权限
	static bool Access(const char* path, int mode);

	/// 根据路径获取文件信息
	/// \param path 文件或目录的路径。
	/// \param info 文件信息，\see FileInfo
	/// \return 是否成功
	static bool Stat(const char* path, FileInfo* info);

protected:

	FileInternal	*m_internal;
};

struct FileFindInternal;

/// \brief 文件查找类，支持'*','?'通配符查找
class CFileFind
{
public:
	CFileFind();
	virtual ~CFileFind();

	/// 查找第一个文件
	/// \param fileName 包含通配符的路径名
	/// \return 是否找到了第一个文件
	virtual bool findFile(const char* fileName);

	/// 查找下一个文件，使用和上次findFile相同的条件，必须在findFile之后调用
	/// \return 是否找到了下一个文件
	virtual bool findNextFile();

	/// 关闭查找，关闭后可以再次调用findFile
	virtual void close();

	/// 得到查找到的文件的长度
	unsigned int getLength();

	/// 得到查找到的文件的文件名
	std::string getFileName();

	/// 得到查找到的文件的全路径
	std::string getFilePath();

	/// 是否为只读文件
	bool isReadOnly();

	/// 是否为目录文件
	bool isDirectory();

	/// 是否为隐藏文件
	bool isHidden();

	/// 是否为普通文件
	bool isNormal();

protected:

	FileFindInternal *m_internal;
};

/// 文件系统操作函数集
struct FSOperations
{
	FILE* (*fopen)(const char *, const char *);
	int (*fclose)(FILE *);
	size_t (*fread)(void *, size_t, size_t, FILE *);
	size_t (*fwrite)(const void *, size_t, size_t, FILE *);
	int (*fflush)(FILE *);
	int (*fseek)(FILE *, long, int);
	long (*ftell)(FILE *);
	char * (*fgets)(char *, int, FILE *);
	int (*fputs)(const char *, FILE *);
	int (*rename)(const char *oldname, const char *newname);
	int (*remove)(const char *path);
	long (*findfirst)(const char *, FileInfo *);
	int (*findnext)(long, FileInfo * );
	int (*findclose)(long);
	int (*mkdir)( const char *dirname);
	int (*rmdir)( const char *dirname);
	int (*statfs)( const char *path, uint64* userFreeBytes, uint64* totalBytes, uint64* totalFreeBytes);
	int (*access)( const char *path, int mode);
	int (*stat)( const char *path, FileInfo *);
};

/// 为了兼容其他非内核文件系统，支持设置钩子接口，通过封装和模拟实现这些接口。
/// \param path 匹配的路径
/// \param opts 文件系统文件操作函数集，0表示取消钩子
void hookFS(const char* path, const FSOperations* opts);


#endif /* FILE_H_ */

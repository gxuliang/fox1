var Session,TimeOut = 0;


$(document).ready(function() 
 	{ 
		window.setInterval("ongetstate('Buf')",1000);
   	} 
);


function getRoot() {
	   var name = {id:1,jsonrpc:"2.0",method:"getroot"};
	   var encoded = $.toJSON( name );
	   var url = "cgi-bin/post.cgi";
	   //alert(url.toString());
	   request.open("POST", url, true);
	   request.onreadystatechange = updateRoot;
	   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
	   var chr = "phone=" + encoded.toString();
	   request.send(chr.toString());
	   //alert("chr is :" + chr.toString());
	   
   }
   
   function updateRoot() {
      if (request.readyState == 4) {
	  //alert("status is fewe");
       if (request.status == 200) {
         var response = request.responseText.split("|");
         //alert("aa:" + response[0].toString());	 

         var obj = jQuery.parseJSON(response[0].toString());
         var name = (obj.pam.base.name.toString());
         var lan = obj.pam.base.lan.toString();
         document.getElementById("macname").value = name;
         document.getElementById("maclan").value = lan;
         $("#resOK").show();
         $("#resOK").hide(2000);
		   
       } else
         alert("status is " + request.status);
     }
   }

function updatelogin() {
	//alert(request.readyState);
	if (request.readyState == 4) {
		if (request.status == 200) {
			var response = request.responseText.split("|");
	        var obj = jQuery.parseJSON(response[0].toString());
	        if(obj.result.toString() == "true")
	        {
	        		Session = obj.session;
	        		//alert(Session);
		        	$("#flogin").hide();
					$("#mbody").show();
				
					
					$(".tab_local").hide(); //Hide all content
					$(".tab_usr").hide(); //Hide all usr
					$(".tab_printview").hide(); //Hide all usr
					$("ul.tabs li:first").addClass("active").show(); //Activate first tab
					$("#tab_local li:first").addClass("active").show(); //Activate first tab
					$(".tab_local:first").show(); //Show first tab content
					$(".width_3_quarter").hide();
					$(".width_full").hide();
				
				
					$("#local").show();
					$("#resOK").hide();

					ongetconfig('base');
	        }
	        else
	        {
		        alert("login failed");
	        }
		}
	}
}

function rpclogin(name,passwd) {
	//var head = {id:11,method:"global.login",params:{version:"1.0",userName:name,password,passwd,clientType, "web",ipAddr:"127.0.0.1"}};
	var params = {version:"1.0",userName:name,password:passwd,clientType:"web",ipAddr:"127.0.0.1"};
	var head = {id:11,jsonrpc:"2.0",method:"global.login"};
	head.params = params;
	var encoded = $.toJSON( head );

	//alert(encoded.toString());
	
	
	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = updatelogin;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());
	
}

function onLogin() {

	var username = document.getElementById("username").value;
	var passwd = document.getElementById("password").value;
	
	//alert(username);
	rpclogin(username,passwd);
	
	return;

}



function onLogout() {
	$("#mbody").hide();
	$("#flogin").show();
	$("ul.tabs li:first").removeClass("active"); //Activate first tab
	
	
}


function updatecamconf() {
	if (request.readyState == 4) {
		if (request.status == 200) {
			var response = request.responseText.split("|");
	        var obj = jQuery.parseJSON(response[0].toString());
	        //alert(obj);
	        if(obj.result.toString() == "true")
	        {
		        var Brightness = obj.params.Encode.CamGlobal.Brightness;
		        var Contrast = obj.params.Encode.CamGlobal.Contrast;
		        var Chromaticity = obj.params.Encode.CamGlobal.Chromaticity;
		        var Saturation = obj.params.Encode.CamGlobal.Saturation;
		        //alert(Saturation);
		        
		        document.getElementById("Brightness").value = Brightness;
		        document.getElementById("Contrast").value = Contrast;
		        document.getElementById("Chromaticity").value = Chromaticity;
				document.getElementById("Saturation").value = Saturation;


	        }
	     }

	}
}

function updateprinter() {
	if (request.readyState == 4) {
		if (request.status == 200) {
			var response = request.responseText.split("|");
	        var obj = jQuery.parseJSON(response[0].toString());
	        for(var key in obj.params)
	        {
	        	if(obj.result.toString() == "true")
	        	{
	        		//var tmp = obj.params;
	        		//alert(tmp[key].prtype);

	        		if(key == "PrinterIn")
	        		{
				        var prtype = obj.params[key].prtype;
				        var prspeed = obj.params[key].prspeed;
				        //var ipaddr = obj.params.Printer.ipaddr;
				        //var welcomeauto = obj.params.Printer.welcomeauto;
				        //alert(Saturation);
				        
				        document.getElementById("iprtype").value = prtype;
				        document.getElementById("iprspeed").value = prspeed;
				        //document.getElementById("ipaddr").value = ipaddr;
						//document.getElementById("welcomeauto").value = welcomeauto;
					}
					else
					{
						var prtype = obj.params[key].prtype;
				        var prspeed = obj.params[key].prspeed;
				        var welcomeauto = obj.params[key].welcomeauto;
				        document.getElementById("oprtype").value = prtype;
				        document.getElementById("oprspeed").value = prspeed;
				        //document.getElementById("ipaddr").value = ipaddr;
						document.getElementById("owelcomeauto").value = welcomeauto;

					}

	        	}

	        }
	     }

	}
}

function ongetprinter(type) {
	if(type == 0)
	{
		nm = "PrinterIn";
	}
	else
	{
		nm = "PrinterOut";
	}
	var params = {name:nm};
	var head = {id:22,jsonrpc:"2.0",method:"configManager.getConfig",session:Session};
	head.params = params;
	var encoded = $.toJSON( head );

	//alert(encoded.toString());
	
	
	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = updateprinter;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());
	
}

function onsetprinter(type) {
	if(type == 0)
	{
		var c_prtype = get_selectop('iprtype'); 
		var c_prspeed = get_selectop('iprspeed'); 
		//var c_welcomeauto = get_selectop('welcomeauto'); 
		//var c_ipaddr = document.getElementById('ipaddr').value; 

		var m_js = {prtype:c_prtype, prspeed:c_prspeed};
		rpcsetconfig("PrinterIn", m_js, updatesetviconf);

	}
	else
	{
		var c_prtype = get_selectop('oprtype'); 
		var c_prspeed = get_selectop('oprspeed'); 
		var c_welcomeauto = get_selectop('owelcomeauto'); 
		//var c_ipaddr = document.getElementById('ipaddr').value; 

		var m_js = {prtype:c_prtype, prspeed:c_prspeed, welcomeauto:c_welcomeauto};
		rpcsetconfig("PrinterOut", m_js, updatesetviconf);

	}
	
	//alert(c_mGOP);
	
}

function updateConfig() {
	if (request.readyState == 4) {
		if (request.status == 200) {
			var response = request.responseText.split("|");
	        var obj = jQuery.parseJSON(response[0].toString());
	        for(var key in obj.params)
	        {
	        	if(obj.result.toString() == "true")
	        	{
	        		//var tmp = obj.params;
	        		//alert(tmp[key].prtype);
	        		//alert(key);
	        		switch(key)
	        		{
	        			case 'base':
	        				
	        				//var hw = obj.params[key].hw;
	        				//alert(hw);
	        				//var lan = obj.params[key].lan;
	        				//var mode = obj.params[key].mode;
	        				//var name = obj.params[key].name;
	        				//var sw = obj.params[key].sw;
	        				document.getElementById("hw").innerText = obj.params[key].hw;
	        				document.getElementById("sw").innerText = obj.params[key].sw;
	       				    document.getElementById("maclan").value = obj.params[key].lan;
	       				    document.getElementById("workmode").value = obj.params[key].mode;
	       				    document.getElementById("macname").value = obj.params[key].name;
	        				break;
	        			default:
	        				break;
	        		}
	        		
	        	}

	        }
	     }

	}
}

function ongetconfig(key) {
	//alert(key);

	var params = {name:key};
	var head = {id:22,jsonrpc:"2.0",method:"configManager.getConfig",session:Session};
	head.params = params;
	var encoded = $.toJSON( head );

	
	
	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = updateConfig;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());
}

function updatestate() {
	//alert(request.readyState);
	if (request.readyState == 4) {
		if (request.status == 200) {
			var response = request.responseText.split("|");
	        var obj = jQuery.parseJSON(response[0].toString());
	        //alert(obj);
	     
	     	var type = obj.params.name.toString();
	     	//alert(type);
	        if(obj.result.toString() == "true")
	        {
	        	switch(type)
	        	{
	        		case "Buf":
	        			//vat buf = 
	        			document.getElementById("pos_buf").value = obj.params.buf.toString();
						document.getElementById("pos_len").innerText = "待处理字节：" + obj.params.len.toString() + "("
												+ (obj.params.pencent/100).toString() + "%)";
						$("div[id=pos_progress]").css("width",(100-obj.params.pencent/100).toString()+"%");
						$("div[id=pos_progress]").css("aria-valuenow",(100-obj.params.pencent/100).toString()+"%");
						$("div[id=pos_progress]").html((100-obj.params.pencent/100).toString()+"%");
						if(obj.params.len.toString() == '0')
						{
							//clearInterval(TimeOut);
							TimeOut = 0;
						}
	        			break;
	        		default:break;
	        	}
		        //var prtype = obj.params.Printer.prtype;
		        //var prspeed = obj.params.Printer.prspeed;
		        //var ipaddr = obj.params.Printer.ipaddr;
		        //var welcomeauto = obj.params.Printer.welcomeauto;
		        //alert(Saturation);
		        
		        //document.getElementById("prtype").value = prtype;
		        //document.getElementById("prspeed").value = prspeed;
		        //document.getElementById("ipaddr").value = ipaddr;
				//document.getElementById("welcomeauto").value = welcomeauto;


	        }
	     }

	}
}

function ongetstate(type) {

	/*
	switch(type)
	{
		case 0://缓冲区状态
			var params = {name:"Buf"};
			break;
		default:break;
	}
	*/

	var params = {name:type};
	var head = {id:22,jsonrpc:"2.0",method:"State.getState",session:Session};
	head.params = params;
	var encoded = $.toJSON( head );

	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = updatestate;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());
}

function sendCmd(type) {

	switch(type)
	{
		case 'TestMsg':
			var msg = document.getElementById("test_buf").value;
			break;
		default:
			break;
	}

	//alert(msg);
	var params = {name:type,data:msg};
	var head = {id:22,jsonrpc:"2.0",method:"State.SendCmd",session:Session};
	head.params = params;
	var encoded = $.toJSON( head );

	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = null;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());
}

function ongetstateTimeOut() {
	//if(TimeOut == 0)
	//	TimeOut = window.setInterval("ongetstate('Buf')",1000);
}




function ongetcamconf() {
	var params = {name:"Encode"};
	var head = {id:22,jsonrpc:"2.0",method:"configManager.getConfig",session:Session};
	head.params = params;
	var encoded = $.toJSON( head );

	//alert(encoded.toString());
	
	
	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = updatecamconf;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());

}

function rpcgetconfig(nm, fun) {
	var params = {name:nm};
	var head = {id:22,jsonrpc:"2.0",method:"configManager.getConfig",session:Session};
	head.params = params;
	var encoded = $.toJSON( head );

	//alert(encoded.toString());
	
	
	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = fun;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());	
}

function set_selectop(id, value) {
    for(var i = 0; i < document.getElementById(id).options.length; i++)
    {
        if(document.getElementById(id).options[i].value == value)
        {	
	        document.getElementById(id).options[i].selected = true;
	        return;
        }
    }
    alert(id+"=error");	
}

function get_selectop(id) {
	for(var i = 0; i < document.getElementById(id).options.length; i++)
	{
		if(document.getElementById(id).options[i].selected == true)
		{
			return document.getElementById(id).options[i].value;
		}
	}
	return null;
}

function updateviconf() {
	if (request.readyState == 4) {
		if (request.status == 200) {
			var response = request.responseText.split("|");
	        var obj = jQuery.parseJSON(response[0].toString());
	        //alert(obj);
	        if(obj.result.toString() == "true")
	        {
	        	//编码模式
		        var mvitype = obj.params.Encode.MainFormat[0].Video.Compression;
		        var evitype = obj.params.Encode.ExtraFormat[0].Video.Compression;
		        //分辨率
		        var mpx = obj.params.Encode.MainFormat[0].Video.PX;
		        var epx = obj.params.Encode.ExtraFormat[0].Video.PX;
		        //
		        var mfps = obj.params.Encode.MainFormat[0].Video.FPS;
		        var efps = obj.params.Encode.ExtraFormat[0].Video.FPS;
		        //码流控制
		        var mstreamctrl = obj.params.Encode.MainFormat[0].Video.StreamMode;
		        var estreamctrl = obj.params.Encode.ExtraFormat[0].Video.StreamMode;
		        //码流大小
		        var mstream = obj.params.Encode.MainFormat[0].Video.Stream;
		        var estream = obj.params.Encode.ExtraFormat[0].Video.Stream;
		        //I帧间隔
		        var mGOP = obj.params.Encode.MainFormat[0].Video.GOP;
		        var eGOP = obj.params.Encode.ExtraFormat[0].Video.GOP;
		       
		        set_selectop("mvtype", mvitype);
		        set_selectop("evtype", evitype);
		        set_selectop("mpx", mpx);
		        set_selectop("epx", epx);
		        set_selectop("mfps", mfps);
		        set_selectop("efps", efps);
		        set_selectop("mStreamMode", mstreamctrl);
		        set_selectop("eStreamMode", estreamctrl);
		        document.getElementById("mstream").value = mstream;
		        document.getElementById("estream").value = estream;
		        document.getElementById("mGOP").value = mGOP;
				document.getElementById("eGOP").value = eGOP;
				
	        }
	     }

	}	
}

function ongetviconf() {
	
	rpcgetconfig("Encode", updateviconf);
}

function updatesetviconf() {
	if (request.readyState == 4) {
		if (request.status == 200) {
			var response = request.responseText.split("|");
	        var obj = jQuery.parseJSON(response[0].toString());
	        //alert(obj);
	        if(obj.result.toString() == "true")
	        {
	        	//alert("ok");
	        	$("#resOK").show();
         		$("#resOK").hide(2000);
	        }
	     }

	}		
}

function rpcsetconfig(nm, jsonobj,fun) {
	var params = {name:nm, table: jsonobj};
	var head = {id:23,jsonrpc:"2.0",method:"configManager.setConfig",session:Session};
	head.params = params;
	var encoded = $.toJSON( head );

	//alert(encoded.toString());
	//return;
	
	var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = fun;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
   var chr = "method=" + encoded.toString();
   //alert(chr.toString());
   request.send(chr.toString());	
}

function onsetviconf() {
	var c_mvitype = get_selectop('mvitype'); 
	var c_mvtype = get_selectop('mvtype'); 
	var c_mpx = get_selectop('mpx'); 
	var c_mfps = get_selectop('mfps'); 
	var c_mStreamMode = get_selectop('mStreamMode'); 
	var c_mstream = document.getElementById('mstream').value; 
	var c_mGOP = document.getElementById('mGOP').value; 
	
	
	//alert(c_mGOP);
	var m_js = {type:c_mvitype, Compression:c_mvtype, PX:c_mpx, FPS:c_mfps, GOP:c_mGOP, StreamMode:c_mStreamMode, Stream:c_mstream};

	//var fps ={FPS:5};
	var mvideo=[];
	mvideo[0] = {Video:m_js};
	var mainformat;
	
	mainformat = {MainFormat:mvideo};
	//alert(mainformat.toString());
	//var table = ;
	//var encoded = $.toJSON( mainformat );
	//alert(encoded.toString());

	//rpcsetconfig("Encode", mainformat, updatesetviconf);
	//return;
	
	var c_eenable = document.getElementById('evable').checked;  
	var c_evitype = get_selectop('evitype'); 
	var c_evtype = get_selectop('evtype'); 
	var c_epx = get_selectop('epx'); 
	var c_efps = get_selectop('efps'); 
	var c_eStreamMode = get_selectop('eStreamMode'); 
	var c_estream = document.getElementById('estream').value; 
	var c_eGOP = document.getElementById('eGOP').value; 
	var e_js = {type:c_evitype, Compression:c_evtype, PX:c_epx, FPS:c_efps, GOP:c_eGOP, StreamMode:c_eStreamMode, Stream:c_estream};
	
	var evideo=[];
	evideo[0] = {Video:e_js,VideoEnable:c_eenable};
	var extraformat;
	extraformat = {ExtraFormat:evideo};
	
	var all = {MainFormat:mvideo, ExtraFormat:evideo};
	rpcsetconfig("Encode", all, updatesetviconf);
}

$(document).ready(function() 
    { 
      	 var TvMode = "PAL";
	var fps;
	if(TvMode == "PAL")
	{
		fps = 25;
	}
	else
	{
		fps = 30;
	}
	var obj1 = document.getElementById('mfps');   
	var obj2 = document.getElementById('efps');  
	for(var i = fps; i > 0; i--)
	{
		obj1.options.add(new Option(i,i),false,false); //这个兼容IE与firefox   
		obj2.options.add(new Option(i,i),false,false);
	}
	   	 } 
);


function keyevent(e) {
	var keynum;

	
	if(window.event) // IE
	{
		keynum = e.keyCode;
	}
	else if(e.which) // Netscape/Firefox/Opera
	{
		keynum = e.which;
	}
	
	//alert(keynum);
	if(keynum == 13)//回车
	{
		onLogin();
	}
}
function onUpgrade(){
	var fname = document.getElementById("filename").value;
	var url = "cgi-bin/post.cgi";
	   //alert(url.toString());
	   request.open("POST", url, true);
	   request.onreadystatechange = updateUpgrade;
	   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
	   var chr = "phone=" + fname.toString();
	   request.send(chr.toString());
	   alert("chr is :" + chr.toString());
}

function updateUpgrade(){
	if (request.readyState == 4) {
	  //alert("status is fewe");
       if (request.status == 200) {
         var response = request.responseText.split("|");
         alert("aa:" + response[0].toString());	 

         
		   
       } else
         alert("status is " + request.status);
     }
}


function operate2(){
	$("#submitForm").ajaxSubmit({  
                    type: 'post',  
                    dataType:"xml",
                    url: "cgi-bin/post.cgi" ,  
                    success: function(data){  
                        alert( "success");  
                        alert(data);
                          
                    },  
                    error: function(XmlHttpRequest, textStatus, errorThrown){  
                        alert( "error");  
                    }  
                });  
                
                return false;
}
 
function operate() {
    // jquery 表单提交
    $("#submitForm").ajaxSubmit(function(message) {
          // 对于表单提交成功后处理，message为提交页面operation.htm的返回内容
          alert(message.toString());
       });
     
    return false; // 必须返回false，否则表单会自己再做一次提交操作，并且页面跳转
}


function doUpload() {
	// 上传方法
	$.upload({
			// 上传地址
			url: '/upload', 
			// 文件域名字
			fileName: 'filedata', 
			// 其他表单数据
			params: {name: 'pxblog'},
			// 上传完成后, 返回json, text
			dataType: 'json',
			// 上传之前回调,return true表示可继续上传
			onSend: function() {
					return true;
			},
			// 上传之后回调
			onComplate: function(data) {
					alert(data);
			}
	});
}

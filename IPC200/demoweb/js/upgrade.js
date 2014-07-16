$(document).ready(function() {
	
	//$("#gdt").hide();
});

var progress = 0;
var sh;
function onupgrade() {
	

   var encoded = 0x02;//update
   var url = "cgi-bin/post.cgi";
   //alert(url.toString());
   request.open("POST", url, true);
   request.onreadystatechange = null;
   request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=gb2312");
   var chr = "method=" + encoded.toString();
   request.send(chr.toString());

	$("#gdt").css("width", String(progress) + "%");
	progress = 0;
	sh = setInterval(query, 1000);
}

function updatequ()
{

	if (request.readyState == 4) {
	//alert("status is fewe");
		if (request.status == 200) {
			var response = request.responseText.split("|");
			var obj = response[0].split("-");

			progress = obj[1];
			$("#gdt").css("width", String(progress) + "%");

			if(progress >= 100)
			{
				clearInterval(sh);
				alert("upgrade successfully, system will reboot!");
			}
			//alert("aa:" + obj[1].toString());	 

			//var obj = jQuery.parseJSON(response[0].toString());
			

		} else
			alert("status is " + request.status);
	}
}
function query()
{
	var encoded = 0x03;//query
	var url = "cgi-bin/post.cgi";
	//alert(url.toString());
	request.open("POST", url, true);
	request.onreadystatechange = updatequ;
	request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=gb2312");
	var chr = "method=" + encoded.toString();
	request.send(chr.toString());


	//progress += 10;
	//$("#gdt").css("width", String(progress) + "%");
	

}

function onNavShow(value) {
	//alert(value);
	$("#yulan").hide();
	$("#yuntai").hide();
	$("#mset").hide();
	$("#nyulan").removeClass("active");
	$("#nyuntai").removeClass("active");
	$("#nset").removeClass("active");
	$("#nalarm").removeClass("active");
	if(value == '1')//预览
	{
		$("#nyulan").addClass("active");
		$("#yulan").show();
	}
	else if(value == '2')
	{
		$("#nyuntai").addClass("active");
		$("#yuntai").show();
	}
	else if(value == '3')
	{
		$("#nset").addClass("active");
		$("#mset").show();
	}
	else if(value == '4')
	{
		$("#nalarm").addClass("active");
		$("#alarm").show();
	}
	else if(value == '5')//注销
	{
		//to do 
	}
}

function onLnavShow(value) {
	$("#sxtsx").hide();
	$("#sp").hide();

  $("#nsxtsx").removeClass("active");
  $("#nsp").removeClass("active");
	if(value == '1')
	{
		$("#sxtsx").show();
    $("#nsxtsx").addClass("active");
	}
	else if(value == '2')
	{
		$("#sp").show();
    $("#nsp").addClass("active");
	}
}

function onRefresh() {
  //alert("www");
}

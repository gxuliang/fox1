$(document).ready(function() {
	
	$("#yuntai").hide();
	$("#mset").hide();
	$('.slider').slider();
	$("#sp").hide();
});


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

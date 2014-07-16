function exvdisable() {
	//alert(document.getElementById("evable").checked);
	if(document.getElementById("evable").checked == false)
	{
		//document.getElementById("evitype").disabled = "disabled";
	}
	else
	{
		//document.getElementById("evitype").disabled = !document.getElementById("evitype").disabled;
	}
}

$(document).ready(function() 
    	{ 
      	  $(".tablesorter").tablesorter(); 
   	 } 
	);


$(document).ready(function() {
	
	$("#mbody").hide();
/*		//When page loads...
	$(".tab_local").hide(); //Hide all content
	$(".tab_usr").hide(); //Hide all usr
	$("ul.tabs li:first").addClass("active").show(); //Activate first tab
	$(".tab_local:first").show(); //Show first tab content
	$(".width_3_quarter").hide();
	$(".width_full").hide();


	$("#local").show();
	$("#resOK").hide();

	
	getRoot();

*/
	//On Click Event
	$("ul.tabs li").click(function() {

		$("ul.tabs li").removeClass("active"); //Remove any "active" class
		//alert(this);
		$(this).addClass("active"); //Add "active" class to selected tab
		$(".tab_local").hide(); //Hide all tab content
		$(".tab_usr").hide(); //Hide all tab usr

		var activeTab = $(this).find("a").attr("href"); //Find the href attribute value to identify the active tab + content
		$(activeTab).fadeIn(); //Fade in the active ID content
		
		return false;
	});
	
	//On Click Event
	$("ul.toggle li").click(function() {

		$(".width_3_quarter").hide();
		$(".width_quarter").hide();
		$(".width_full").hide();
		$(".tab_local").hide(); //Hide all content
		$(".tab_usr").hide(); //Hide all usr


		var activeTab = $(this).find("a").attr("href"); //Find the href attribute value to identify the active tab + content
		$(activeTab).fadeIn(); //Fade in the active ID content		
		
		var aa = ".tab_" + activeTab.substr(1) + ":first";
		//alert(aa);
		$("ul.tabs li").removeClass("active"); //Remove any "active" class
		var bb = "#tab_" + activeTab.substr(1) + " li:first";
		$(bb).addClass("active").show(); //Activate first tab
		$(aa).show(); //Show first tab content
		
		
		return false;
	});

});

libname trees '/home/u63792450/sasuser.v94/SAS statistics/Project2';

data trees.birthweight;
	set sashelp.bweight;
	count + 1;
run;

proc hpsplit data=trees.birthweight seed=123;
	class black boy married momedlevel momsmoke;
	model weight=black boy married momedlevel 
	momsmoke momage momwtgain visit cigsperday;
	output out=trees.bwregout;
run;

proc hpsplit data=trees.birthweight seed=123 plots=zoomedtree(nodes=("0") depth=2 fracprec=4 
		predictorprec=4) nodes;
	class black boy married momedlevel momsmoke;
	model weight=black boy married momedlevel momsmoke momage momwtgain visit 
		cigsperday;
	output out=bwregout;
run;

proc hpsplit data=trees.birthweight seed=123 plots=zoomedtree(nodes=("9") depth=4 fracprec=4 
		predictorprec=4) nodes;
	class black boy married momedlevel momsmoke;
	model weight=black boy married momedlevel momsmoke momage momwtgain visit 
		cigsperday;
run;

proc univariate data=bwregout;
	class _node_;
	var weight;
	output out=bwuni p1=p1 p5=p5 p10=p10;
run;

proc sort data=bwuni;
	by p10;
run;

proc print data=bwuni;
run;

data trees.bwregout;
	set bwregout;
	retain possdigs 
		'0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';

	do power=0 to 100 while(62**power<=_NODE_);
	end;
	left=_NODE_;
	length node $10;
	node=' ';
	i=0;

	do power=power-1 to 0 by -1;
		i+1;
		r=int(left/(62**power));
		substr(node, i, 1)=substr(possdigs, r+1, 1);
		left=left-(62**power)*r;
	end;
run;
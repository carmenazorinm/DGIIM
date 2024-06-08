*ods pdf file="/home/u63792450/sasuser.v94/SAS statistics/SecondTry/hyp_test.pdf";
*ods pdf close;
LIBNAME lib "/home/u63792450/sasuser.v94/SAS statistics/Project";

PROC IMPORT OUT=lib.quantity_reduction 
		DATAFILE="/home/u63792450/sasuser.v94/SAS statistics/Project/reduct_qty.CSV" 
		DBMS=CSV REPLACE;
	GETNAMES=YES;
RUN;

PROC IMPORT OUT=lib.release_info DATAFILE="/home/u63792450/sasuser.v94/SAS statistics/Project/estimateRelease.CSV" 
		DBMS=CSV REPLACE;
	GETNAMES=YES;
RUN;

DATA lib.release_info;
	SET lib.release_info;
	RENAME rel_est_amt=release_estimation_amount;
RUN;

* transform string to integer;

DATA lib.quantity_reduction(KEEP=tri_facility_id energy_onsite_qty 
		recyc_onsite_qty treated_onsite_qty);
	SET lib.quantity_reduction;
	energy_onsite_qty=INPUT(energy_onsite_curr_yr_qty, comma12.);
	recyc_onsite_qty=INPUT(recyc_onsite_curr_yr_qty, comma12.);
	treated_onsite_qty=INPUT(treated_onsite_curr_yr_qty, comma12.);
RUN;

PROC SORT DATA=lib.quantity_reduction;
BY tri_facility_id;
RUN;

PROC SORT DATA=lib.release_info;
	BY tri_facility_id;
RUN;

DATA lib.combined_data;
	MERGE lib.quantity_reduction (keep=tri_facility_id energy_onsite_qty 
		recyc_onsite_qty treated_onsite_qty) lib.release_info (keep=tri_facility_id 
		release_estimation_amount environmental_medium);
	BY tri_facility_id;
RUN;

* exclude missing data;

DATA lib.combined_data;
	SET lib.combined_data;

	IF NOT MISSING(release_estimation_amount);

	IF NOT MISSING(treated_onsite_qty);

	IF NOT MISSING(energy_onsite_qty);

	IF NOT MISSING(recyc_onsite_qty);
RUN;

/* FIRST RESEARCH QUESTION*/
PROC MEANS DATA=lib.combined_data NOPRINT;
	CLASS environmental_medium;
	VAR release_estimation_amount;
	OUTPUT out=release_stats MEAN=mean_amount MEDIAN=median_amount n=NOBS;
RUN;

PROC PRINT DATA=release_stats;
	TITLE 
		'Descriptive Statistics for Release Estimation Amounts by Environmental Medium';
	VAR environmental_medium mean_amount median_amount NOBS;
RUN;

PROC SGPLOT DATA=release_stats;
	TITLE 'Release Estimation Amounts by Environmental Medium';
	VBAR environmental_medium / RESPONSE=mean_amount DATALABEL=mean_amount;
RUN;

PROC GLM DATA=lib.combined_data;
	CLASS environmental_medium;
	MODEL release_estimation_amount=environmental_medium;
	LSMEANS environmental_medium / PDIFF;
	RUN;

	/* SECOND RESEARCH QUESTION */
PROC MEANS DATA=lib.combined_data MEAN MEDIAN STD;
	VAR energy_onsite_qty recyc_onsite_qty treated_onsite_qty 
		release_estimation_amount;
	TITLE 'Descriptive Statistics for Quantity Reduction and Release Information';
RUN;

PROC SGPLOT DATA=lib.combined_data;
	TITLE 
		'Relationship Between Energy Quantity Reduction and Release Estimation Amount';
	scatter x=energy_onsite_qty y=release_estimation_amount / 
		markerattrs=(symbol=circlefilled);
	xaxis label='Energy Onsite Quantity';
	yaxis label='Release Estimation Amount';
RUN;

PROC SGPLOT DATA=lib.combined_data;
	TITLE 'Relationship Between Teated Chemicals Quantity Reduction and Release Estimation Amount';
	scatter x=treated_onsite_qty y=release_estimation_amount / 
		markerattrs=(symbol=circlefilled);
	xaxis label='Treated Chemicals Onsite Quantity';
	yaxis label='Release Estimation Amount';
RUN;

PROC SGPLOT DATA=lib.combined_data;
	TITLE 'Relationship Between Recycling Quantity Reduction and Release Estimation Amount';
	scatter x=recyc_onsite_qty y=release_estimation_amount / 
		markerattrs=(symbol=circlefilled);
	xaxis label='Recycling Onsite Quantity';
	yaxis label='Release Estimation Amount';
RUN;

PROC ANOVA DATA=lib.combined_data;
	CLASS recyc_onsite_qty treated_onsite_qty energy_onsite_qty;
	MODEL release_estimation_amount=recyc_onsite_qty treated_onsite_qty 
		energy_onsite_qty recyc_onsite_qty*treated_onsite_qty 
		recyc_onsite_qty*energy_onsite_qty energy_onsite_qty*treated_onsite_qty;
	MEANS recyc_onsite_qty treated_onsite_qty energy_onsite_qty/ tukey cldiff;
	RUN;

	/* INCLUDE DISTANCE TO WORK */
PROC IMPORT OUT=lib.facility_information DATAFILE="/home/u63792450/sasuser.v94/SAS statistics/Project/facility_information.CSV" 
		DBMS=CSV REPLACE;
	GETNAMES=YES;
RUN;

DATA lib.facility_information_decimal(DROP=fac_latitud fac_long);
	SET lib.facility_information;
	fac_latitud=fac_latitude;
	lat_sec=input(substr(fac_latitud, length(fac_latitud)-1, length(fac_latitud)), 
		best2.);
	fac_latitud=input(substr(fac_latitud, 1, length(fac_latitud)-2), best12.);
	lat_min=input(substr(fac_latitud, length(fac_latitud)-1, length(fac_latitud)), 
		best2.);
	lat_deg=input(substr(fac_latitud, 1, length(fac_latitud)-2), best12.);
	fac_long=fac_longitude;
	long_sec=input(substr(fac_long, length(fac_long)-1, length(fac_long)), best2.);
	fac_long=input(substr(fac_long, 1, length(fac_long)-2), best12.);
	long_min=input(substr(fac_long, length(fac_long)-1, length(fac_long)), best2.);
	long_deg=input(substr(fac_long, 1, length(fac_long)-2), best12.);
RUN;

DATA lib.facility_information_decimal(DROP=lat_sec lat_min lat_deg long_sec 
		long_min long_deg);
	SET lib.facility_information_decimal;
	facility_latitude_decimal=lat_deg+lat_min/60+lat_sec/3600;
	facility_longitude_decimal=long_deg+long_min/60+long_sec/3600;
RUN;

DATA lib.facility_distance_to_los_angeles;
	SET lib.facility_information_decimal;

	/* Calculate distance to Los Angeles (34°03'08.1"N, 118°14'37.3"W) */
	distance_to_los_angeles=GEODIST(facility_latitude_decimal, 
		-facility_longitude_decimal, 34.0523, -118.2437, 'M');

	/* Coordinates of Los Angeles in decimal degrees */
	DROP fac_latitude fac_longitude facility_latitude_decimal 
		facility_longitude_decimal;
RUN;

/* RESEARCH QUESTION WITH DISTANCE */
PROC SORT DATA=lib.facility_distance_to_los_angeles;
	BY tri_facility_id;
RUN;

DATA combined_data_with_distance;
	MERGE lib.combined_data lib.facility_distance_to_los_angeles;
	BY tri_facility_id;
RUN;

PROC RANK DATA=combined_data_with_distance OUT=combined_data_with_distance 
		groups=10 /* Specify the number of distance groups */;
	var distance_to_los_angeles;
	ranks distance_group;
RUN;

PROC GLM DATA=combined_data_with_distance;
	CLASS distance_group;
	MODEL release_estimation_amount=distance_group;
	MEANS distance_group / tukey cldiff;
	TITLE 'One-way ANOVA: Release Estimation Amount by Distance Group';
	RUN;
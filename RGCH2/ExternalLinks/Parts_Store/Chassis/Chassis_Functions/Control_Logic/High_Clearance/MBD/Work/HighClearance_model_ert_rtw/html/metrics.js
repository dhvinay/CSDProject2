function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["look1_iflf_binlca"] = {file: "C:\\Dev\\Chassis_Development\\RGCH2\\ExternalLinks\\Parts_Store\\Chassis\\Chassis_Functions\\Control_Logic\\High_Clearance\\MBD\\Work\\slprj\\ert\\_sharedutils\\look1_iflf_binlca.c",
	stack: 20,
	stackTotal: 20};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="HighClearance_model_metrics.html">Global Memory: 0(bytes) Maximum Stack: 20(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();

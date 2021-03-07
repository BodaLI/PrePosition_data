
void AllData::Parameter_assign() {
	vector<double> temp_p_s(simu_times, 1.0 / double(simu_times));
	p_s = temp_p_s;
	p_0 = temp_p_s;
	// Parameters related to ambiguity set
	theta = double(simu_times) / double(simu_times) / 2.0 * log(2.0 * double(simu_times) / (1 - confidient_level));
	UB = 1e8;					// Upper bound
	LB = -1e8;				// Lower bound
	con_tol = 0.1;		// Convergence tolerance
}

void AllData::DNR_data_assign() {
	double S_base;		// MW
	double V_base;		// kV
	double X_base;		
	// DLine
	int line_num;
	vector<vector<int>> line_node_pair;
	vector<double> line_R;		// ohm
	vector<double> line_X;		// ohm
	vector<double> line_S_max;		// kVA
	// Pole
	vector<int> line_pole_number;		// number of poles on each line
	vector<double> pole_lambda_1;
	vector<double> pole_lambda_2;
	// DNode
	int node_num;
	vector<double> node_Pl; // Load P, MW
	vector<double> node_Ql; // Load Q, MVar
	vector<double> node_V_min;
	vector<double> node_V_max;
	vector<double> node_factor;
	vector<double> node_per_value;	// Value of loads
	// Charging station
	int cha_stat_num;
	vector<int> cha_node;					// Location of the charging station
	vector<double> Cha_cap;				// Capacity of the charging station
	vector<double> cha_Qmax;			// Reactive power capacity of the charging station
	// Feeder
	int FD_num;							// Number of feeders
	vector<int> FD_node;			// Location of feeders
	// Diesel Generator
	int DG_num;
	vector<int> DG_node;		// Location of DGs
	vector<double> DG_Pmax;			// Maximum active power output of DG
	vector<double> DG_Qmax;			// Maximum reactive power output of DG

	if (Case == "033Bus") {
		S_base = 100;			// MW
		V_base = 12.66;		// kV
		X_base = V_base * V_base / S_base;		// p.u. for resistance

		// Branch data
		line_num = 37;
		line_node_pair = { {1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{2,19},{19,20},{20,21},{21,22},{3,23},{23,24},{24,25},{6,26},{26,27},{27,28},{28,29},{29,30},{30,31},{31,32},{32,33},{8,21},{9,15},{12,22},{18,33},{25,29} };
		line_R = { 0.0922,0.4930,0.3660,0.3811,0.8190,0.1872,0.7114,1.0300,1.0440,0.1966,0.3744,1.4680,0.5416,0.5910,0.7463,1.2890,0.7320,0.1640,1.5042,0.4095,0.7089,0.4512,0.8980,0.8960,0.2030,0.2842,1.0590,0.8042,0.5075,0.9744,0.3105,0.3410,2.0000,2.0000,2.0000,0.5000,0.5000 };
		line_X = { 0.0470,0.2511,0.1864,0.1941,0.7070,0.6188,0.2351,0.7400,0.7400,0.0650,0.1238,1.1550,0.7129,0.5260,0.5450,1.7210,0.5740,0.1565,1.3554,0.4784,0.9373,0.3083,0.7091,0.7011,0.1034,0.1447,0.9337,0.7006,0.2585,0.9630,0.3619,0.5302,2.0000,2.0000,2.0000,0.5000,0.5000 };
		vector<double> t_line_S_max(line_num, 0.05);		
		line_S_max = t_line_S_max;
		// R/X标幺化
		for (size_t i_l = 0; i_l < line_num; ++i_l) {
			line_R[i_l] = line_R[i_l] / X_base;
			line_X[i_l] = line_X[i_l] / X_base;
		}

		// Pole data
		line_pole_number = { 5, 8, 8, 8, 6, 9, 5, 8, 5, 9, 5, 5, 5, 8, 3, 4, 8, 9, 6, 4, 10, 9, 7, 6, 7, 4, 7, 7, 6, 4, 7, 9, 6, 6, 10, 9, 6 };
		vector<double> t_pole_lambda_1(line_num, 0.00005);		
		vector<double> t_pole_lambda_2(line_num, 0.042);
		pole_lambda_1 = t_pole_lambda_1;
		pole_lambda_2 = t_pole_lambda_2;

		// Bus data
		node_num = 33;
		node_Pl = { 0, 100, 90, 120, 60, 60, 200, 200, 60, 60, 45, 60, 60	, 120	, 60, 60	, 60, 90, 90, 90, 90, 90, 90, 420, 420, 60, 60, 60, 120, 200, 150, 210, 60 };	// kW
		node_Ql = { 0, 60, 40, 80, 30, 20, 100, 100, 20, 20, 30, 35, 35, 80, 10, 20, 20, 40, 40, 40, 40, 40, 50, 200, 200, 25, 25, 20, 70, 600, 70, 100, 40 };			// Load Q, kVar
		vector<double> t_node_V_min(node_num, 0.9);
		vector<double> t_node_V_max(node_num, 1.1);
		vector<double> t_node_factor(node_num, 0.9);
		node_V_min = t_node_V_min;
		node_V_max = t_node_V_max;
		node_factor = t_node_factor;
		node_per_value = { 90, 20, 20, 80, 70, 50, 30, 20, 20, 40, 100, 30, 50, 60, 90, 90, 20, 80, 30, 40, 70, 80, 20, 50, 50, 20, 80, 40, 60, 60, 60, 90, 70 };		// $/kWh 
		// P/Q标幺化
		for (size_t i_n = 0; i_n < node_num; ++i_n) {
			node_Pl[i_n] = node_Pl[i_n] / 1000 / S_base;	// p.u. transformation
			node_Ql[i_n] = node_Ql[i_n] / 1000 / S_base;
		}

		// Charging station
		cha_stat_num = 3;
		cha_node = { 9, 18, 29 };
		Cha_cap = { 15, 15, 15 };						
		cha_Qmax = { 0.045, 0.045, 0.045 };
		// Feeder
		FD_num = 1;
		FD_node = { 1 };
		// Diesel generator
		DG_num = 1;
		DG_node = { 15 };
		DG_Pmax = { 0.001 };
		DG_Qmax = { 0.001 };
		// Sources set at different time
		all_src = { 1,9,15,18,29 };
	}
	else {
		string Case_Warn = "Case does not exist!";
		cout << Case_Warn << endl;
	}
	// Value Assignment
	for (size_t i_node = 0; i_node < node_num + 1; ++i_node)
	{	// Virtual node has been taken into account
		Nodes temp_all_node;
		if (i_node == 0)
		{	// Virtual node
			temp_all_node.node_id = i_node;
			temp_all_node.node_name = to_string(i_node);
		}
		else
		{
			temp_all_node.node_id = i_node;
			temp_all_node.node_name = to_string(i_node);
			temp_all_node.p_load = node_Pl[i_node - 1];
			temp_all_node.q_load = node_Ql[i_node - 1];
			temp_all_node.V_min = node_V_min[i_node - 1];
			temp_all_node.V_max = node_V_max[i_node - 1];
			temp_all_node.factor = node_factor[i_node - 1];
			temp_all_node.e_loss = node_per_value[i_node - 1];
		}
		allNode.push_back(temp_all_node);
	}
	// Value assignment for DSLine obj
	for (size_t i_line = 0; i_line < line_num; ++i_line)
	{
		DLines temp_DS_line;
		temp_DS_line.line_id = i_line;
		temp_DS_line.node_1_id = line_node_pair[i_line][0];
		temp_DS_line.node_1_name = allNode[temp_DS_line.node_1_id].node_name;
		temp_DS_line.node_2_id = line_node_pair[i_line][1];
		temp_DS_line.node_2_name = allNode[temp_DS_line.node_2_id].node_name;

		string temp_line_name = "line_" + temp_DS_line.node_1_name + "_" + temp_DS_line.node_2_name;
		temp_DS_line.line_name = temp_line_name;
		temp_DS_line.R = line_R[i_line];
		temp_DS_line.X = line_X[i_line];
		temp_DS_line.S_max = line_S_max[i_line];
		allDLine.push_back(temp_DS_line);
	}

	// Value assignment for distribution poles on each line
	for (size_t i_line = 0; i_line < line_num; ++i_line) {
		vector<Poles> temp_pole_vec;
		for (size_t i_pole = 0; i_pole < line_pole_number[i_line]; ++i_pole) {
			Poles temp_pole;
			temp_pole.line_id = allDLine[i_line].line_id;
			temp_pole.lambda_1 = pole_lambda_1[i_line];
			temp_pole.lambda_2 = pole_lambda_2[i_line];
			temp_pole_vec.push_back(temp_pole);
		}
		allPole.push_back(temp_pole_vec);
	}

	vector<int> AllSrc;
	// Value assignment for ChargeSta obj
	for (size_t i_sta = 0; i_sta < cha_stat_num; ++i_sta)
	{
		ChargeStas temp_eb_sta;
		temp_eb_sta.sta_id = i_sta;
		temp_eb_sta.node_id = cha_node[i_sta];
		temp_eb_sta.node_name = allNode[temp_eb_sta.node_id].node_name;
		temp_eb_sta.Ccap = Cha_cap[i_sta];
		temp_eb_sta.Q_max = cha_Qmax[i_sta];
		all_sta.push_back(temp_eb_sta);
		AllSrc.push_back(temp_eb_sta.node_id);
	}
	// Value assignment for Feeder obj
	for (size_t i_fd = 0; i_fd < FD_num; ++i_fd)
	{
		FDnode temp_fd;
		temp_fd.fd_id = i_fd;
		temp_fd.node_id = FD_node[i_fd];
		temp_fd.node_name = allNode[temp_fd.node_id].node_name;
		all_fd.push_back(temp_fd);
		AllSrc.push_back(temp_fd.node_id);
	}
	// Value assignment for DG obj
	for (size_t i_dg = 0; i_dg < DG_num; ++i_dg)
	{
		DGnode temp_dg;
		temp_dg.dg_id = i_dg;
		temp_dg.node_id = DG_node[i_dg];
		temp_dg.node_name = allNode[temp_dg.node_id].node_name;
		temp_dg.P_max = DG_Pmax[i_dg];
		temp_dg.Q_max = DG_Qmax[i_dg];
		all_dg.push_back(temp_dg);
		AllSrc.push_back(temp_dg.node_id);
	}
	// Value assignment for Virtual line
	for (size_t i_po = 0; i_po < AllSrc.size(); ++i_po)
	{
		VLines temp_vline;
		temp_vline.vline_id = i_po;
		temp_vline.node_1_id = 0;
		temp_vline.node_2_id = AllSrc[i_po];
		allVLine.push_back(temp_vline);
	}
	//------------------------------------------------------------

	cout << "Value assignment for the PDN is finished" << endl;
}

void AllData::TN_data_assign() {
	if (Case == "033Bus") {
		// 5 roads
		int road_num = 5;
		vector<vector<double>> failure_prob_each_road = { {0.45, 0.6, 0.75, 0.9}, {0.0,0.05,0.15,0.25}, {0.02,0.05,0.1,0.25}, {0.05,0.15,0.25,0.30}, {0.05,0.1,0.15,0.3} };
		vector<vector<double>> road_rainfall_range = { {200,400},{400,600},{600,800},{800,1000} };	

	   // 4 routes
		int route_num = 4;
		vector<int> route_EB_min = { 6,8,7,8 };
		vector<int> route_EB_max = { 10,15,12,13 };
		vector<int> route_EB_for_DS = { 5,7,6,7 };
		vector<vector<int>> route_road_belong = { {1,3,5},{2,3,5},{2,3,4},{2,5} };		// relationship between routes and road
		vector<vector<int>> route_stat_belong = { {9,18},{9,18},{18,29},{9,29} };			// relationships between route and station
		vector<vector<double>> route_stat_cost = { {150,145},{145,140},{150,140},{140,150} };		


		// Value assignment for road objects
		for (size_t i_road = 0; i_road < road_num; ++i_road)
		{
			Road temp_road;
			temp_road.road_id = i_road + 1;
			temp_road.road_status = 1;
			temp_road.failure_prob_sup = failure_prob_each_road[i_road];
			temp_road.rainfall_range = road_rainfall_range;
			all_road.push_back(temp_road);
		}
		// Value assignment for route objects
		for (size_t i_route = 0; i_route < route_num; ++i_route) {
			// 行车路线编号#1 - #4
			Route temp_route;
			temp_route.route_id = i_route + 1;
			temp_route.EB_min = route_EB_min[i_route];
			temp_route.EB_max = route_EB_max[i_route];
			temp_route.EB_max_for_DS = route_EB_for_DS[i_route];
			temp_route.road_id = route_road_belong[i_route];
			temp_route.sta_id = route_stat_belong[i_route];
			temp_route.rou_2_sta_cost_eachEB = route_stat_cost[i_route];
			all_route.push_back(temp_route);
		}
	}
	else {
		string Case_Warn = "Case data of TN does not exist!";
		cout << Case_Warn << endl;
	}
	cout << "Value assignment for the transportation network is finished" << endl;
}

void AllData::func_scenario_gene() {

	// Part I: Simulation of failures caused by the gale
	int time_section = 7;
	vector<double> wind_speed = { 10, 30, 70, 10, 60, 30, 10 };		// Wind speed data for sampling
	vector<double> all_line_failure_prob_whole_process;

	// Step 1: Failure probability of poles and lines at different stages
	for (int i_line = 0; i_line < allDLine.size(); ++i_line) {
		vector<double> line_failure_prob_each_stage;
		for (size_t i_stage = 0; i_stage < time_section; ++i_stage) {
			double p_each_pole_fail_each_stage = allPole[i_line][0].lambda_1 * exp(allPole[i_line][0].lambda_2 / 0.45*wind_speed[i_stage]);	// mph to m/s
			if (p_each_pole_fail_each_stage >= 1) {
				p_each_pole_fail_each_stage = 1;
			}
			// Line failure probability at stage i_stage
			double p_each_line_fail_stage = 1 - pow(1 - p_each_pole_fail_each_stage, allPole[i_line].size());
			line_failure_prob_each_stage.push_back(p_each_line_fail_stage);
		}
		double temp_single_line_fail_whole_process = 1;
		for (size_t i_stage = 0; i_stage < time_section; ++i_stage) {
			temp_single_line_fail_whole_process = temp_single_line_fail_whole_process * (1 - line_failure_prob_each_stage[i_stage]);
		}
		all_line_failure_prob_whole_process.push_back(1 - temp_single_line_fail_whole_process);
	}

	// Step 2: Failure scenario generation with failure probability
	srand(t1);
	for (size_t i_sce = 0; i_sce < simu_times; ++i_sce) {
		vector<BrokeLine> t_all_bline_s;
		for (int i_line = 0; i_line < allDLine.size(); ++i_line) {
			double p_rand_each_line = rand() / double(RAND_MAX);
			if (p_rand_each_line < all_line_failure_prob_whole_process[i_line]) {
				BrokeLine temp_bline;
				temp_bline.b_node = allDLine[i_line].node_1_id;
				temp_bline.e_node = allDLine[i_line].node_2_id;
				t_all_bline_s.push_back(temp_bline);
			}
		}
		all_bline_s.push_back(t_all_bline_s);		
	}

	// Part II: Simulations for the heavy rain drop
	vector<double> all_road_failure_prob;
	double rainfall = 500;			// unit: mm 
	for (size_t i_road = 0; i_road < all_road.size(); ++i_road) {
		for (size_t i_interval = 0; i_interval < all_road[i_road].rainfall_range.size(); ++i_interval) {
			if ((rainfall >= all_road[i_road].rainfall_range[i_interval][0]) && (rainfall < all_road[i_road].rainfall_range[i_interval][1])) {
				all_road_failure_prob.push_back(all_road[i_road].failure_prob_sup[i_interval]);
				break;
			}
		}
	}
	srand(t2);
	for (size_t i_sce = 0; i_sce < simu_times; ++i_sce) {
		vector<BrokeRoad> t_all_broad_s;
		for (int i_road = 0; i_road < all_road.size(); ++i_road) {
			double p_rand_each_road = rand() / double(RAND_MAX);
			if (p_rand_each_road < all_road_failure_prob[i_road]) {
				BrokeRoad temp_broad;
				temp_broad.road_id = all_road[i_road].road_id;
				t_all_broad_s.push_back(temp_broad);
			}
		}
		all_broad_s.push_back(t_all_broad_s);		
	}

}


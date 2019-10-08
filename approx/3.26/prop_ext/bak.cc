	/*	if (CG_lb[i] <= 0)
		{
			CG_lb_ind[i] = -1;
			cout << "CG_lb_ind[" << i << "] = " << CG_lb_ind[i] << endl;
			continue;
		}
		if (CG_lb[i] == S_sum[i-1])
		{
			CG_lb_ind[i] = i-1;
			cout << "CG_lb_ind[" << i << "] = " << CG_lb_ind[i] << endl;
			continue;
		}
		for (int j = i-1; j > 0; j--)
		{
			if (CG_lb[i] < S_sum[j] && CG_lb[i] >= S_sum[j-1])
			{
				if (CG_lb[i] > S_sum[j-1])
					CG_lb_ind[i] = j;
				else if (CG_lb[i] == S_sum[j-1])
					CG_lb_ind[i] = j-1;
				break;
			}
		}	
	*/

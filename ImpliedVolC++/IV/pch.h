// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#ifndef PCH_H
#define PCH_H

template<typename Function>
double SolveByBisect(Function* Fct, double Tgt, double LEnd, double REnd, double Acc)
{
	double left = LEnd, right = REnd, mid = (left + right) / 2;
	double y_left = Fct->Value(left) - Tgt, y_mid = Fct->Value(mid) - Tgt;
	while (mid - left > Acc)
	{
		if ((y_left > 0 && y_mid > 0) || (y_left < 0 && y_mid < 0))
		{
			left = mid; y_left = y_mid;
		}
		else right = mid;
		mid = (left + right) / 2;
		y_mid = Fct->Value(mid) - Tgt;
	}
	return mid;
}
template<typename Function>
double SolveByNR(Function* Fct, double Tgt, double Guess, double Acc)
{
	double x_prev = Guess;
	double x_next = x_prev - (Fct->Value(x_prev) - Tgt) / Fct->Deriv(x_prev);
	while (x_next - x_prev > Acc || x_prev - x_next > Acc)
	{
		x_prev = x_next;
		x_next = x_prev - (Fct->Value(x_prev) - Tgt) / Fct->Deriv(x_prev);
	}
	return x_next;
}


#endif //PCH_H

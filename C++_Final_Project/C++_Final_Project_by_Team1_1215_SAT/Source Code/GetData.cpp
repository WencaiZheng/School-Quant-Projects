#include"GetData.h"

using namespace std;
void GetTxt(Team& Category, string file)
{
	string ticker, start, end, act_eps, est_eps;
	//Read file.
	ifstream infile(file);
	while (infile.good())
	{
	// Read data for ticker, startTime and endTime, store them.
		getline(infile, ticker, '\t');
		getline(infile, start, '\t');
		getline(infile, end, '\t');
		getline(infile, act_eps, '\t');
		getline(infile, est_eps, '\n');
	// Use the constructor to creat stock and push into category.
		Category.StockList.insert(pair<string, Stock>(ticker, Stock(ticker, start, end, act_eps, est_eps)));
		Category.Ticker.push_back(ticker);
	}
}

struct MemoryStruct
{
	char *memory;
	size_t size;
};

size_t write_data(void *ptr, int size, int nmemb, FILE *stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void *myrealloc(void *ptr, size_t size)
{
	/* There might be a realloc() out there that doesn't like reallocing
	NULL pointers, so we take care of it here */
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

size_t write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

string getTimeinSeconds(string Time)
{
	std::tm t = { 0 };
	std::istringstream ssTime(Time);
	char time[100];
	memset(time, 0, 100);
	if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
	{
		//cout << std::put_time(&t, "%c %Z") << "\n"<< std::mktime(&t) << "\n";
		sprintf_s(time, "%lld", mktime(&t));
		return string(time);
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}
// Return the error message if occurred.
int GetStockPrice(Team& Category)
{
	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;
	//file pointer to create file that store the data  
	FILE *fp;
	//declaration of an object CURL 
	CURL *handle;
	//result of the whole process 
	CURLcode result;
	curl_global_init(CURL_GLOBAL_ALL);
	handle = curl_easy_init();
	if (handle)
	{
		string sCookies, sCrumb;
		if (sCookies.length() == 0 || sCrumb.length() == 0)
		{
			//curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history?p=AMZN");
			curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
			curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);

			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			char cKey[] = "CrumbStore\":{\"crumb\":\"";
			char *ptr1 = strstr(data.memory, cKey);
			char *ptr2 = ptr1 + strlen(cKey);
			char *ptr3 = strstr(ptr2, "\"}");
			if (ptr3 != NULL)
				*ptr3 = NULL;
			sCrumb = ptr2;
			fp = fopen("cookies.txt", "r");
			char cCookies[100];
			if (fp) {
				while (fscanf(fp, "%s", cCookies) != EOF);
				fclose(fp);
			}
			else
				cerr << "cookies.txt does not exists" << endl;
			sCookies = cCookies;
			free(data.memory);
			data.memory = NULL;
			data.size = 0;
		}
		map<string, Stock>::iterator itr = Category.StockList.begin();
		while (true)
		{
			if (itr == Category.StockList.end())
				break;

			// Input the start time and end time for certain stock.
			string Tail = "T16:00:00";
			string startTime = getTimeinSeconds(itr->second.GetStartTime() + Tail);
			string endTime = getTimeinSeconds(itr->second.GetEndTime() + Tail);

			string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
			string symbol = itr->second.GetTicker();
			string urlB = "?period1=";
			string urlC = "&period2=";
			string urlD = "&interval=1d&events=history&crumb=";
			string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
			const char * cURL = url.c_str();
			const char * cookies = sCookies.c_str();
			curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
			curl_easy_setopt(handle, CURLOPT_URL, cURL);
			stringstream Info;
			struct MemoryStruct temp_ptr;
			temp_ptr.memory = NULL;
			temp_ptr.size = 0;
			string temp_line;

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&temp_ptr);
			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}
			Info.str(temp_ptr.memory);
			getline(Info, temp_line);// Pop out the first line.
			for (int j = 0; j < 241; j++)
			{
				getline(Info, temp_line, ',');//Date
				itr->second.Date.push_back(temp_line.c_str());
				getline(Info, temp_line, ',');//Open
				getline(Info, temp_line, ',');//High
				getline(Info, temp_line, ',');//Low
				getline(Info, temp_line, ',');//Close
				getline(Info, temp_line, ',');//Adj close
				//push back price
				itr->second.Price.push_back(atof(temp_line.c_str()));
				getline(Info, temp_line, '\n');//Volume
			}
			free(temp_ptr.memory);
			temp_ptr.size = 0;
			// For Testing if the length of the vector is 241.
			cout << itr->second.GetTicker() << " completed." << '\n';
			itr++;
		}
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}
	curl_easy_cleanup(handle);

	curl_global_cleanup();
	return 0;
}

int GetIWBPrice(Stock& IWB)
{

	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;
	//file pointer to create file that store the data  
	FILE *fp;
	CURL *handle;
	CURLcode result;
	//curl_global_init(CURL_GLOBAL_ALL);
	handle = curl_easy_init();
	if (handle)
	{
		string sCookies, sCrumb;
		if (sCookies.length() == 0 || sCrumb.length() == 0)
		{
			//curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history?p=AMZN");
			curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
			curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
			result = curl_easy_perform(handle);
			if (result != CURLE_OK)
			{
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}
			char cKey[] = "CrumbStore\":{\"crumb\":\"";
			char *ptr1 = strstr(data.memory, cKey);
			char *ptr2 = ptr1 + strlen(cKey);
			char *ptr3 = strstr(ptr2, "\"}");
			if (ptr3 != NULL)
				*ptr3 = NULL;
			sCrumb = ptr2;
			fp = fopen("cookies.txt", "r");
			char cCookies[100];
			if (fp) {
				while (fscanf(fp, "%s", cCookies) != EOF);
				fclose(fp);
			}
			else
				cerr << "cookies.txt does not exists" << endl;
			sCookies = cCookies;
			free(data.memory);
			data.memory = NULL;
			data.size = 0;
		}
		// Input the start time and end time for certain stock.
		string Tail = "T16:00:00";
		string startTime = getTimeinSeconds(IWB.GetStartTime() + Tail);
		string endTime = getTimeinSeconds(IWB.GetEndTime() + Tail);
		string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
		string symbol = IWB.GetTicker();
		string urlB = "?period1=";
		string urlC = "&period2=";
		string urlD = "&interval=1d&events=history&crumb=";
		string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
		const char * cURL = url.c_str();
		const char * cookies = sCookies.c_str();
		curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
		curl_easy_setopt(handle, CURLOPT_URL, cURL);

		stringstream Info;
		struct MemoryStruct temp_ptr;
		temp_ptr.memory = NULL;
		temp_ptr.size = 0;
		string temp_line;

		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&temp_ptr);
		result = curl_easy_perform(handle);

		if (result != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return 1;
		}

		Info.str(temp_ptr.memory);

		getline(Info, temp_line);// Pop out the first line.
		for (int j = 0; j < 496; j++)
		{
			getline(Info, temp_line, ',');//Date
			string date = temp_line.c_str(); // date
			getline(Info, temp_line, ',');//Open
			getline(Info, temp_line, ',');//High
			getline(Info, temp_line, ',');//Low
			getline(Info, temp_line, ',');//Close
			getline(Info, temp_line, ',');//Adj close				   
			double price = atof(temp_line.c_str());//price
			getline(Info, temp_line, '\n');//Volume
			IWB.Date.push_back(date);//push back date
			IWB.Price.push_back(price);//push back price

		}
		free(temp_ptr.memory);
		temp_ptr.size = 0;

	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	curl_easy_cleanup(handle);

	curl_global_cleanup();
	return 0;
}
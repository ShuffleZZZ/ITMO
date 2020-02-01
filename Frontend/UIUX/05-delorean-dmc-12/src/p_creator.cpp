#include<fstream>

/*int main()
{
	std::ifstream in;
	in.open("tweets.txt");
	std::ofstream out;
	out.open("tweets_in_p.txt");
	while(in)
	{
		std::string tweet;
		getline(in, tweet);
		out << "<p>" << tweet << "<\p>\n";
	}
	in.close();
	out.close();
}*/

/*int main()
{
	std::ifstream in;
	in.open("tweets_in_p.txt");
	std::ofstream out;
	out.open("tweets_in_p_without_telegram.txt");
	while(in)
	{
		std::string tweet;
		getline(in, tweet);
		bool cut_off = 0;
		for (int i = 0; i < tweet.size(); ++i) {
			std::size_t found_link = tweet.find("t.co");
			std::size_t found_advert = tweet.find("telegram");
			std::size_t found_mention = tweet.find("@");
			if (found_link != std::string::npos ||
				found_advert != std::string::npos ||
				found_mention != std::string::npos) cut_off = 1;
		}
		if (!cut_off) {
			out << tweet << '\n';
		}
		
	}
	in.close();
	out.close();
}*/


int main()
{
	std::ifstream in;
	in.open("tweets_in_p_without_telegram.txt");
	std::ofstream out;
	out.open("final.txt");
	while(in)
	{
		std::string tweet;
		getline(in, tweet);
		if (tweet.size() > 2 &&
			tweet[tweet.size() - 1] == '>' &&
			tweet[tweet.size() - 2] == 'p' &&
			tweet[tweet.size() - 3] == '<')
			{
				for (int i = 0; i < tweet.size() - 2; ++i) {
					out << tweet[i];
				}
				out << "/p>\n";
			} else {
				out << tweet;
			}
	}
	in.close();
	out.close();
}



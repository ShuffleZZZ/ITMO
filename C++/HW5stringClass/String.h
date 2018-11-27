#pragma once

class String {
	public:
		explicit String(const int size);
		String(const std::string arg); // C-type
		explicit String(const int amount, const char fill);
		String(const String& arg);

		void append(const String& arg);
		void swap(String& arg);
		void reverse();
		void copy(const int begin, const int end, String& out); // end is non-strict boarder
		short strcmp(const String& arg) const;
				
		int getSize() const;
		char* getStr() const;
		
		String& operator =(const String& arg);
		
		bool operator <(const String& second) const;
		bool operator <=(const String& second) const;
		bool operator >(const String& second) const;
		bool operator >=(const String& second) const;
		bool operator ==(const String& second) const;
		bool operator !=(const String& second) const;
		
		~String();
	private:
		int mSize;
		char* mStr;
};

std::ostream& operator <<(std::ostream& out, const String& arg);

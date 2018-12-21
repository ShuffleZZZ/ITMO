#pragma once

const unsigned int COLOR_BITS = 8, COLOR_MASK = (1 << COLOR_BITS) - 1;
const std::string FORMAT_TYPE = "P2";

class Picture
{
	public:
		explicit Picture(const unsigned int height, const unsigned int width);
		Picture(const Picture& arg);
		
		Picture operator +(const Picture& arg) const; // mixture of pictures.
		Picture operator -(const Picture& arg) const; // light out second picture in the first one.
		Picture operator *(const Picture& arg) const; // usually selfmultiply, increases contrast.
		
		Picture& operator +=(const Picture& arg);
		Picture& operator -=(const Picture& arg);
		Picture& operator *=(const Picture& arg);
		
		Picture operator +(const int arg) const; // makes darker on constant.
		Picture operator -(const int arg) const; // makes brighter on constant.
		Picture operator *(const unsigned int arg) const; // makes darker in scale.
		Picture operator /(const unsigned int arg) const; // makes brighter in scale.
		Picture operator %(const unsigned int arg) const; // shows colors lighter than arg.
		
		Picture& operator +=(const int arg);
		Picture& operator -=(const int arg);
		Picture& operator *=(const unsigned int arg);
		Picture& operator /=(const unsigned int arg);
		Picture& operator %=(const unsigned int arg);
		
		Picture& operator ~(); //color inversion.
		
		Picture operator ^(const Picture& arg) const; // inversion according to arg's colors.
		Picture operator &(const Picture& arg) const; // common colors only.
		Picture operator |(const Picture& arg) const; // all colors of both pictures.
		
		Picture& operator ^=(const Picture& arg);
		Picture& operator &=(const Picture& arg);
		Picture& operator |=(const Picture& arg);
		
		Picture operator ^(const int arg) const; // inversion relative to arg color.
		Picture operator &(const int arg) const; // arg color filter.
		Picture operator |(const int arg) const; // adds arg color to picture.
		Picture operator >>(const unsigned int arg) const; // contrast decrease.
		Picture operator <<(const unsigned int arg) const; // contrast increase.
		
		Picture& operator ^=(const int arg);
		Picture& operator &=(const int arg);
		Picture& operator |=(const int arg);
		Picture& operator >>=(const unsigned int arg);
		Picture& operator <<=(const unsigned int arg);
				
		bool operator <(const Picture& r) const;
		bool operator <=(const Picture& r) const;
		bool operator >(const Picture& r) const;
		bool operator >=(const Picture& r) const;
		bool operator ==(const Picture& r) const;
		bool operator !=(const Picture& r) const;
		
		Picture& operator +(); // clockwise rotation.
		Picture& operator -(); // anti-clockwise rotation.
		
		//increments are used to equal height before panorama.
		void operator ++(); // pre, adds top raw.
		void operator --(); // pre, removes top raw.
		void operator ++(const int); // post, adds bottom raw.
		void operator --(const int); // post, removes bottom raw.
		
		explicit operator bool() const;
		operator !() const;
		bool operator &&(const Picture& r) const;
		bool operator ||(const Picture& r) const;
		
		Picture& operator =(const Picture& arg);
		
		Picture operator ,(const Picture& arg) const; //makes panorama (needs same height).
		
		void operator ->*(const std::string fileName) const; // save to file.
		void get(const std::string fileName); // gets from file.
		
		std::vector <int>& operator [](const unsigned int i);
		const std::vector <int>& operator [](const unsigned int i) const;
		
		unsigned int getHeight() const;
		unsigned int getWidth() const;
		void swap(Picture& arg);
		
		~Picture();
	private:
		unsigned int mHeight;
		unsigned int mWidth;
		std::vector <std::vector <int>> mArray;
		
		short cmp(const Picture& r) const; // compare resolution.
};

std::ostream& operator <<(std::ostream& out, const Picture& arg);
std::istream& operator >>(std::istream& in, Picture& arg);

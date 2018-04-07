 #include <iostream> 
 
 using namespace std; 

class animals { 
	protected: 
		int count; 
	public: 
		animals() { } 
		animals (int a) { 
			count=a; 
		} 
		virtual void sound (){ 
			cout<<"RRR!!!"<<"\n"; 
		} 
		void num(){ 
			cout<<count<<"\n"; 
		} 
}; 

class dog:public animals { 
	public: 
		dog():animals() {}; 
		dog(int a) { 
			count=a; 
		}; 
		void sound(int a) { 
			if (a % 3==0){ 
				cout<<"Rrr"<<"\n"; 
			} 
			if (a % 3==1){ 
				cout<<"RRR!!! AV!!!"<<"\n"; 
			} 
			if (a % 3==2){ 
				cout<<"Gav! Gav!"<<"\n"; 
			} 
		} 
}; 

class goat:public animals { 
	public: 
		goat():animals() {}; 
		goat(int a) { 
			count=a; 
		}; 
		void sound(int a) { 
			if (a % 2==0){ 
				cout<<"Meee"<<"\n"; 
			} 
			if (a % 2==1){ 
				cout<<"Beee"<<"\n"; 
			} 
		} 
}; 

class fishes:public animals { 
	public: 
		fishes() {}; 
		fishes(int b) { 
			count=b; 
		}; 
		int staya() { 
			if (count>10) 
				cout<<"Staya"<<"\n"; 
			else 
				cout<<"Malo"<<"\n"; 
		} 
}; 

int main() {  
	fishes Guppi(4); 
	dog Haski(6); 
	goat Mout(3); 
	Haski.sound(1); 
	Mout.sound(4); 
	Guppi.staya();
}

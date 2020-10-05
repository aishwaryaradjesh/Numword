#include <cstdio>
#include <cstring>
#include<string>
#include <cmath>

namespace bw{

    static const char * ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    static const char * teens[] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
    static const char * tens[]= {"Error", "Error", "twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
    static const char * hundreds_ = "hundred";
    static const char * powers_[] = {"Error","thousand","million","billion","trillion","quadrillion"};
    static const char * hyphen_ = " - ";
    static const char * space_ = " ";
    
    class numword{

        std::string  _s = "string";
        uint64_t _num = 0;
        char * buf_ = nullptr;
        size_t buflen = 0;
        size_t max_len = 1024;
        void clearbuf();
        void initbuf();
        void appendbuf(const char *);
        public:
        numword() : _num(0) {}
        numword(const uint64_t & num) : _num(num) {}
        ~numword();
        
        
        const char * word(uint64_t n);


    };
    numword::~numword() {
    clearbuf();
}


    const char * numword::word(uint64_t n)
        {
            int sum = n;
            
            constexpr uint64_t _maxnum = 999999999999999999;
            const char * s;
            const char * s_cat = "";
            
            initbuf();
            if(n> _maxnum){
                s_cat = "Error";
                return s_cat;
            }
            if(n == 0){
                s_cat = "Zero";
            }
            if(n >= 1000 ){
                for(int i=5; i>0 ; i--){
                    uint64_t pow_ = (uint64_t) pow(1000.0,i);
                    uint64_t n_ = (n - (n % pow_))/ pow_;
                    if(n_){
                        numword _nw;
                        appendbuf(" ");
                        appendbuf(_nw.word(n_));
                        appendbuf(" ");
                        appendbuf(powers_[i]);
                        //s_cat = s_cat + space_ + word(n_)+ space_ + powers_[i]; 

                        n = n - (n_ * pow_);
                    }
                   
                }
            }
            if(n >=100 && n < 1000){
                appendbuf(" ");
                numword _nw;
                appendbuf(_nw.word(n/100));
                appendbuf(" ");
                appendbuf(hundreds_);
                
                n = n % 100;
            }
            if(n>=20 && n<100){
                appendbuf(" ");
                appendbuf(tens[n/10]);
                
                n = n % 10;
            }
            if(n>=10 && n<20){
                n = n - 10;
                appendbuf(" ");
                appendbuf(teens[n]);
                
                n=0;
            }
            if(n> 0 && n <10){
                appendbuf(" ");
                appendbuf(ones[n]);
               

            }
            
            return buf_;
            
        }
        void numword::clearbuf() {
            if (buf_ != nullptr) {
                delete [] buf_;
                buf_ = nullptr;
            }
            buflen = 0;
        }
        void numword::initbuf() {
            clearbuf();
            try {
                buf_ = new char[max_len];
                *buf_ = 0;
                //hyphen_flag = false;
            } catch (std::bad_alloc e) {
                printf("numword: cannot allocate buffer: %s\n", e.what());
            }
        }
        void numword::appendbuf(const char * s){
            size_t stlen = strnlen(s, max_len);
            if(stlen < 1){
                return;
            }
            if(buflen + stlen + 1 >=max_len){
                return;
            }
            memcpy(buf_+ buflen, s, stlen);
            buflen += stlen;
            buf_[buflen] = 0;
            
        }

}

   



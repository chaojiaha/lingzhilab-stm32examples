/*
查找质数示例
*/

#define BAUD 9600

// 定义一个byte类型的数组，并初始化
byte primes[]={ 
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
    102, 107, 109, 113, 127, 131,  137 , 139, 149, 151, 157, 163, 167, 173,  179, 181, 191, 193, 197, 
    199, 211, 223, 227, 229, 233, 239, 241, 251 };

// 如果你把上面的数组类型更改为 int，那么下面这行要更改为
// "const int TopPrimeIndex = (sizeof(primes)/2) - 1;"

const unsigned int TopPrimeIndex = sizeof(primes) - 1;      
const unsigned long TopPrimeSquared = (long)primes[TopPrimeIndex] * (long)primes[TopPrimeIndex];
int primeFlag;


void setup()                   
{
  pinMode(33, OUTPUT);
  Serial.begin(BAUD);  

  delay(5000);

  Serial.print("数组中元素的个数：");
  Serial.println(TopPrimeIndex);
  Serial.println();
  Serial.print("数组中最后一个元素的值： ");
  Serial.println((unsigned int)primes[TopPrimeIndex]);
  Serial.println();

  Serial.print("数组最后一个元素平方值： ");
  Serial.println(TopPrimeSquared);
  Serial.println();


}
void loop()                     
{
    for (long x = 1; x < TopPrimeSquared; x+=2){  // 跳过包括2在内的偶数，使算法更快

            for (long j=0; j < TopPrimeIndex; j++){
              primeFlag = true;

              if (x == primes[j]) break;

              if (x % primes[j] == 0){     // if the test number modolo (next number from prime table) == 0 
                primeFlag = false;       //  then test number is not prime, bailout and check the next number
                break;
            }
        }
        if (primeFlag == true){           // found a prime - print it
            Serial.println(x);
       }
    }
}

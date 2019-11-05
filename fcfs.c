#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main()
{
	for (int i = 0; i <=3; ++i)
	{
		/* code */
		if(fork()==0)
		{
			volatile int a=5,i=0;
			for(;i<4e7;i++)
				a+=(int)(3.14*6.23);
			printf(1,"%d\n",a );
		}
	}
	for (int i = 0; i <=3; ++i)
	{
		wait();
		/* code */
	}
}
#include <systemc.h>
#include "conio.h"
#include "top.h"

#define clockcycle 10 // 10ns = 100MHz
#define maxcycle   3000
#define maxtime    maxcycle*clockcycle


int sc_main(int argc, char *argv[])
{

    char *filename;
	bool dolog;

	if (argc<2) {
	    printf("Usage:8051_iss filename imagename\n");
	    return(1);
	}
	if (argc<3) {
	    printf("Usage:8051_iss filename imagename\n");
	    return(1);
	}
	filename=argv[1];
        sc_clock clk("CLOCK", clockcycle, SC_NS, 0.5, 0, SC_NS, true);
        sc_signal<sc_uint<1> >  reset;
        sc_signal<bool >  rst_n;
        sc_signal<sc_uint<1> >  poff;
		
		rst_n.write(1);
	
        top top("top");
        top.clk(clk);
        top.reset(reset);
        top.poff(poff);
		

        if (!top.core->loadrom(filename)) {
            printf("%s file not found\n",filename);
            return(1);
        }
		filename=argv[2];
		{
			FILE *FR;
			unsigned char s;
			int i;
			FR=fopen(filename,"rb");
			if (FR==NULL) {printf("%s file not found\n",filename);return(1);}
			for(i=0;i<8*8;i++)
			{
				s=fgetc(FR);
				top.xrambig->mem[(0x3000)+i]=s;
			}
			fclose (FR);
		}


        ///////////////////////////////////Start Test
		ECC_mon mon0("ECC_monitor");
		mon0.P0(top.port0o);
		mon0.P1(top.port1o);
		mon0.P2(top.port2i);
		mon0.P3(top.port3i);
		mon0.rst_n(rst_n);
		mon0.clk(clk);

        // sc_start(maxtime, SC_NS);	

		sc_trace_file* Tf;
		Tf = sc_create_vcd_trace_file("waveform");
		sc_trace(Tf, clk, "clk");

		sc_trace(Tf, top.port0o, "port0o");
		sc_trace(Tf, top.port1o, "port1o");
		sc_trace(Tf, top.port2i, "port2i");
		sc_trace(Tf, top.port3i, "port3i");

		sc_start(maxtime, SC_NS);
		sc_close_vcd_trace_file(Tf);

        return(0);
}

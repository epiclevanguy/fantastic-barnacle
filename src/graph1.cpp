#include "graph.h"
#include "nauty.h"

void Graph::PrintAVTCount()
{
        DYNALLSTAT(graph,g,g_sz);
        DYNALLSTAT(int,lab,lab_sz);
        DYNALLSTAT(int,ptn,ptn_sz);
        DYNALLSTAT(int,orbits,orbits_sz);
        static DEFAULTOPTIONS_GRAPH(options);
        statsblk stats;

        int n, m;

        //options.writeautoms = TRUE;

        n = MATRIX_V.size();
        m = SETWORDSNEEDED(n);

        nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

        DYNALLOC2(graph,g,g_sz,m,n,"malloc");
        DYNALLOC1(int,lab,lab_sz,n,"malloc");
        DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
        DYNALLOC1(int,orbits,orbits_sz,n,"malloc");

        EMPTYGRAPH(g,m,n);
        for (int i = 0 ; i < MATRIX_V.size() ; ++i)
        {
            for (int j = i + 1 ; j < MATRIX_V.size() ; ++j)
            {
                if(MATRIX_V[i][j])
                {
                    ADDONEEDGE(g,i,j,m);
                }
            }
        }

        densenauty(g,lab,ptn,orbits,&options,&stats,m,n,NULL);

        printf("Automorphism count = ");
        writegroupsize(stdout,stats.grpsize1,stats.grpsize2);
        printf("\n");
}


#ifdef COMPILE_QPSWIFT

#include "qps_wrap.h"

VectorXd qpSwiftSolve(QP *qpp, int var_size, int const_size, MatrixXd &H, VectorXd &G, MatrixXd &A, VectorXd &Ub, bool verbose)
{
    qp_int n = var_size;   /*! Number of Decision Variables */
    qp_int m = const_size; /*! Number of Inequality Constraints */
    qp_int p = 0;          /*! Number of equality Constraints */

    qpp = QP_SETUP_dense(n, m, 0, H.data(), NULL, A.data(), G.data(), Ub.data(), NULL, NULL, COLUMN_MAJOR_ORDERING);

    qp_int ExitCode = QP_SOLVE(qpp);

    if (verbose)
    {
        if (qpp != NULL)
            printf("Setup Time     : %f ms\n", qpp->stats->tsetup * 1000.0);
        if (ExitCode == QP_OPTIMAL)
        {
            printf("Solve Time     : %f ms\n", (qpp->stats->tsolve + qpp->stats->tsetup) * 1000.0);
            printf("KKT_Solve Time : %f ms\n", qpp->stats->kkt_time * 1000.0);
            printf("LDL Time       : %f ms\n", qpp->stats->ldl_numeric * 1000.0);
            printf("Diff	       : %f ms\n", (qpp->stats->kkt_time - qpp->stats->ldl_numeric) * 1000.0);
            printf("Iterations     : %ld\n", qpp->stats->IterationCount);
            printf("Optimal Solution Found\n");
        }
        if (ExitCode == QP_MAXIT)
        {
            printf("Solve Time     : %f ms\n", qpp->stats->tsolve * 1000.0);
            printf("KKT_Solve Time : %f ms\n", qpp->stats->kkt_time * 1000.0);
            printf("LDL Time       : %f ms\n", qpp->stats->ldl_numeric * 1000.0);
            printf("Diff	       : %f ms\n", (qpp->stats->kkt_time - qpp->stats->ldl_numeric) * 1000.0);
            printf("Iterations     : %ld\n", qpp->stats->IterationCount);
            printf("Maximum Iterations reached\n");
        }

        if (ExitCode == QP_FATAL)
        {
            printf("Unknown Error Detected\n");
        }

        if (ExitCode == QP_KKTFAIL)
        {
            printf("LDL Factorization fail\n");
        }
    }

    VectorXd ret;
    ret.setZero(n);
    for (int i = 0; i < n; i++)
    {
        ret(i) = qpp->x[i];
    }

    QP_CLEANUP_dense(qpp);

    return ret;
}

#endif
#ifndef TPC_COMPUTATION_HPP
#define TPC_COMPUTATION_HPP

#include <vector>
#include <string>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <fstream>


// lambda, threshold, weight)

class TPComputation
{
    public:
        void init_TPComputation(const int& NDOF, const float& lambda, const float& threshold, const float& weight);
        void clear_TPComputation();

        // da chiamare per ogni TASK nella gerarchia, una volta mandato il comando distruggo l'oggetto della classe
        void computeTP_step(const std::string& task_id, const Eigen::MatrixXd& ActivationFnc, const Eigen::MatrixXd& TaskJac, const Eigen::VectorXd& TaskRef);

        Eigen::MatrixXd getTP_ydot();
        Eigen::MatrixXd getTP_Q();

        // internal methods
        Eigen::MatrixXd REG_Pinv_operator(const Eigen::MatrixXd& ProjJac, const Eigen::MatrixXd& act, const Eigen::MatrixXd proj);
        Eigen::MatrixXd REG_Pinv(const Eigen::MatrixXd& mat);
        double DecreasingBellShapedFunction(double xmin, double xmax, double ymin, double ymax, double x);

    private:
        // old step matrices
        Eigen::MatrixXd Q;
        Eigen::MatrixXd y;

        Eigen::MatrixXd Qold;
        Eigen::MatrixXd yold;

        // temp matrices to avoid redefinition
        // TC step
        Eigen::MatrixXd W;
        
        Eigen::MatrixXd ProjJac;
        Eigen::MatrixXd Xq;
        Eigen::MatrixXd XI;
        // REG pinv op
        Eigen::MatrixXd TaskOr_reg;
        Eigen::MatrixXd CtrlDr_reg;
        Eigen::MatrixXd Pinv;
        // REG pinv
        Eigen::MatrixXd S_pinv;
        Eigen::MatrixXd V;
        Eigen::MatrixXd U;
        Eigen::VectorXd S;

        // velcity vector dimension
        int ndof_;

        // init flags
        bool is_first_step_;

        // parameters used in the pseudo-inverse regularization
        float lambda_;      
        float threshold_;
        float weight_;
};


#endif //TPC_COMPUTATION_HPP
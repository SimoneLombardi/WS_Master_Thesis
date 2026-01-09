#include "TPComputation.hpp"


void TPComputation::init_TPComputation(const int& ndof, const float& lambda, const float& threshold, const float& weight)
{
    ndof_ = ndof; 
    lambda_ = lambda;
    threshold_ = threshold;
    weight_ = weight;

    is_first_step_ = true;
}

void TPComputation::clear_TPComputation()
{
    Q.resize(0,0);
    y.resize(0,0);
}

double TPComputation::DecreasingBellShapedFunction(double xmin, double xmax, double ymin, double ymax, double x){
    double y;
    if (x <= xmin)
        y = ymax;
    else if (x >= xmax)
        y = ymin;
    else
    {
        double cosarg = (x - xmin) * M_PI / (xmax - xmin);
        y = (ymax - ymin) * (0.5 * cos(cosarg) + 0.5) + ymin;
    }
    return y;
}

Eigen::MatrixXd TPComputation::REG_Pinv(const Eigen::MatrixXd& mat)
{
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(mat, Eigen::ComputeFullU | Eigen::ComputeFullV);
    //Eigen::LLT<Eigen::MatrixXd> svd(mat, Eigen::ComputeFullU | Eigen::ComputeFullV);
    V = svd.matrixV();
    U = svd.matrixU();
    S = svd.singularValues();

    int row = mat.rows();
    int col = mat.cols();
    int r = std::min(row, col);
    S_pinv = Eigen::MatrixXd::Zero(col, row);
    //Eigen::DiagonalMatrix<double, Eigen::Dynamic> SS_pinv = (Eigen::VectorXd::Zero(r)).asDiagonal();

    for(int i = 0; i < r; i++)
    {
        double SingV = DecreasingBellShapedFunction(0, threshold_, 0, lambda_, S(i));
        S_pinv(i,i) = S(i) /(S(i) * S(i) + SingV);
        //SS_pinv.diagonal()(i) = S(i) /(S(i) * S(i) + SingV);
    }

    // std::cout << "V dimensions: " << V.rows() << " x " << V.cols() << std::endl;
    // std::cout << "S_pinv dimensions: " << S_pinv.rows() << " x " << S_pinv.cols() << std::endl;  
    // std::cout << "U.transpose() dimensions: " << U.transpose().rows() << " x " << U.transpose().cols() << std::endl;

    return V * S_pinv * U.transpose();
}

Eigen::MatrixXd TPComputation::REG_Pinv_operator(const Eigen::MatrixXd& ProjJac, const Eigen::MatrixXd& act, const Eigen::MatrixXd proj)
{
    // save dimension for the task jacobian
    const int jrows = ProjJac.rows();
    const int jcols = ProjJac.cols();

    // J'*(I-A)*A*J -> task oriented regularization
    TaskOr_reg = ProjJac.transpose() * (Eigen::MatrixXd::Identity(jrows, jrows)-act) * act * ProjJac;

    // control direcion regularization 
    CtrlDr_reg = weight_*((Eigen::MatrixXd::Identity(jcols, jcols) - proj).transpose()*(Eigen::MatrixXd::Identity(jcols, jcols) - proj));

    // 
    Pinv = REG_Pinv(ProjJac.transpose()*act.transpose()*act*ProjJac + TaskOr_reg + CtrlDr_reg);

    return Pinv*ProjJac.transpose()*act.transpose()*act;
}


void TPComputation::computeTP_step(const std::string& task_id, const Eigen::MatrixXd& ActivationFnc, const Eigen::MatrixXd& TaskJac, const Eigen::VectorXd& TaskRef)
{
    //save dimension
    int actR = ActivationFnc.rows();
    int actC = ActivationFnc.cols();
    int TjcR = TaskJac.rows();
    int TjcC = TaskJac.cols();
    //
    if(actR==actC && TjcR==actR){
        if(is_first_step_){
            //std::cout << "\033[1;34m INIT TP ALG\033[0m\n" << std::endl;
            Q = Eigen::MatrixXd::Identity(TjcC, TjcC);
            y = Eigen::MatrixXd::Zero(ndof_, 1);
            is_first_step_ = false;
        }
    } else{
        //std::cout << "[TPComputation::computeTP_step] ERROR: Act func and Task Jac dim! .. " << task_id << std::endl;
        std::cout << "[TPComp]: "<< TaskRef.rows() << "." << TaskRef.cols() << "//" << ActivationFnc.rows() << "." << ActivationFnc.cols() << "//" << TaskJac.rows() << "." << TaskJac.cols() << std::endl; 
        return;
    }

    Qold = Q;
    yold = y;
    Eigen::MatrixXd eye = Eigen::MatrixXd::Identity(TjcC,TjcC);

    ProjJac = TaskJac * Qold; // project the current task jacobian in the KERNEL of the previous step
    Xq = REG_Pinv_operator(ProjJac, ActivationFnc, Qold);
    XI = REG_Pinv_operator(ProjJac, ActivationFnc, eye);


    W = ProjJac * Xq;
    
    Q = Qold * (eye - XI * ProjJac);
    
    y = yold + Qold * XI * W * (TaskRef - TaskJac * yold);
}

Eigen::MatrixXd TPComputation::getTP_ydot()
{
    return y;
}

Eigen::MatrixXd TPComputation::getTP_Q()
{
    return Q;
}



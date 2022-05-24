#ifndef WBHQP_CONTACTCONSTRAINT_HPP
#define WBHQP_CONTACTCONSTRAINT_HPP

#include "rbdl/rbdl.h"
#include <iostream>
#include <Eigen/Dense>
#include "math.h"
#include "wbd.h"

using namespace Eigen;

#define CONTACT_CONSTRAINT_ZMP 4
#define CONTACT_CONSTRAINT_FORCE 6
#define CONTACT_CONSTRAINT_PRESS 3

namespace DWBC
{

    enum
    {
        CONTACT_6D,
        CONTACT_POINT,
    };

    class ContactConstraint
    {
    private:
        /* data */
    public:
        bool contact;

        Vector3d xc_pos;
        int link_id_;
        int link_number_;
        Matrix3d rotm;

        unsigned int contact_type_; // 0 : 6dof contact, 1 : point Contact
        unsigned int contact_dof_;
        unsigned int constraint_number_;

        std::vector<unsigned int> constraint_m_;

        Vector3d contact_point_;
        Vector3d contact_direction_;

        MatrixXd j_contact;

        double contact_plane_x;
        double contact_plane_y;

        double friction_ratio_x;
        double friction_ratio_y;
        double friction_ratio_z;

        ContactConstraint();
        ContactConstraint(RigidBodyDynamics::Model &md_, int link_number, int link_id, int contact_type, Vector3d contact_point, Vector3d contact_vector, double lx, double ly);

        ~ContactConstraint();

        void Update(RigidBodyDynamics::Model &model_, const VectorXd q_virtual_);
        void SetContact(bool cont);

        void EnableContact();

        void DisableContact();
        void SetFrictionRatio(double x, double y, double z);
        MatrixXd GetZMPConstMatrix4x6();

        MatrixXd GetForceConstMatrix6x6();
        MatrixXd GetContactConstMatrix();

        MatrixXd GetPressConstMatrix3x6();
    };
}

#endif
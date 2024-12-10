#ifndef RMATRIX_LIMITED_CALCULATOR_H
#define RMATRIX_LIMITED_CALCULATOR_H

#include "ReconResonance/RmatrixLimited/endf/LIST.h"
#include "ReconResonance/RmatrixLimited/endf/LTT1.h"
#include "ReconResonance/RmatrixLimited/rml/System.h"
#include "ReconResonance/RmatrixLimited/rml/TwoBody.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"

#include "Config/CommonData.hpp"
#include "CommonUtils/VectorCopier.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "MathUtils/MathUtils.hpp"

namespace frendy
{
  //class RmatrixLimitedCalculator : public virtual LRU0, public virtual LIST
  class RmatrixLimitedCalculator :  public virtual ENDF::LIST
  {
    public:

  //--------------------------------------------------
  /*!
      @brief A solver for the RML cross-sections
  */
  //--------------------------------------------------

    class Solver : public RML::System
    {
      vector<RML::TwoBody> partitions;  // partitions
      vector<double>       qvalues;     // reaction Q-values
      vector<double>       eths;        // thresold energies of the reaction
      int n;                            // number of the partitions (or Q-values)

     public:

      Solver();
     ~Solver();

      const RML::TwoBody& Partition( const int i ) const;
            RML::TwoBody& Partition( const int i );
      const double&  Qvalue   ( const int i ) const;
            double&  Qvalue   ( const int i );
      const double&  Ethre    ( const int i ) const;
            double&  Ethre    ( const int i );

      int size() const { return n; }

      void Clear();

      void PushBack( const double J, const int pi );
      void PushBack( const RML::TwoBody& partition );
      void PushBack( const RML::TwoBody& partition,
                     const double& qvalue, const double& eth );

      void Run( const double elab, double* result );
      void Run( const double elab, vector<double>* result );

      void Run( LIST* result );
      void Run( const double elab, vector<ENDF::LTT1::Record>* result );
    };

    protected:
      frendy::ErrorManager    err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      Solver sol_obj;

      frendy::ResonanceDataContainer      reso_data_obj;
      frendy::RMatrixLimitedDataContainer r_matrix_data_obj;

      int iso_ene_set_flg;
      int iso_no, reso_ene_no, react_no;
      vector<int> react_type_list;

      vector<Real8>        q_vec, eth_vec;

      //void run( const RML::TwoBody& inc, double& elab,
      //          const RML::TwoBody& out, vector<double>& result );

      void check_reso_data();
      void set_particle_pair_data();
      void set_spin_data();
      void set_gam_width_data(int i, Real8 aj, int pi);
      void set_gam_width_data_channel(int i, Real8 aj, int pi);
      void set_gam_width_data_reduced(int i, Real8 aj, int pi);
      void set_threshold_data();

//      double sign( double x );

    public:
      //constructor
      RmatrixLimitedCalculator();

      //destructor
      virtual ~RmatrixLimitedCalculator();

      void clear();

      void calc_resonance_xs( Real8 elab, vector<Real8>& result, vector<Integer>& react_type_vec );
      void calc_resonance_xs( Real8 elab, vector<Real8>& result );
      //void calc_angular_distr( Real8 elab, vector<vector<Real8> >& result );

      void set_resonance_data(int nis, int ner);
      void set_resonance_data(frendy::RMatrixLimitedDataContainer data_obj);

      void set_reso_data_obj( frendy::ResonanceDataContainer data_obj );

      frendy::ResonanceDataContainer      get_reso_data_obj();
      frendy::RMatrixLimitedDataContainer get_r_matrix_data_obj();
      vector<int>                         get_react_type_list();
      vector<Real8>                       get_q_val();
      vector<Real8>                       get_eth_val();
  };
}

#endif //RMATRIX_LIMITED_CALCULATOR_H

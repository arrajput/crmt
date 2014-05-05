//////////////////////////////////////////////////////////////////////
/// \class Module
/// \file Module.h
/// \brief A class which describes a single module
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <vector>

namespace sim {

  class Module {
  
  private:

    unsigned int fModuleType;
    double       fScintWidth;
    double       fScintHeight;
    double       fScintGap;
    double       fModGap;
    double       fScintShift;
    double       fScintLength;
    double       fGap;
  
    std::map<int, std::pair<double,double> > fFiberMap; ///< map of fiber locations
  
  public:

    /// Default constructor takes no arguments
    Module();

    /// Constructor used takes module type and gap arguments
    Module(const unsigned int& module_type, const double& gap);

    /// Virtual destructor
    virtual ~Module();
    
    void SetType(const unsigned int& type);
    void SetGap(const double& gap);

    const std::map<int, std::pair<double,double> >& GetMap()         const;
    unsigned int                                    GetModuleType()  const;
    double                                          GetScintLength() const;

  };

}

inline const std::map<int, std::pair<double,double> >& sim::Module::GetMap()         const { return fFiberMap;    }
inline unsigned int                                    sim::Module::GetModuleType()  const { return fModuleType;  } 
inline double                                          sim::Module::GetScintLength() const { return fScintLength; }

#endif

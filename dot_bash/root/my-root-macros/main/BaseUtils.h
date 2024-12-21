//
//  BaseUtils.h
//
//  Created by Yasser Corrales Morales on 5/19/15.
//  Copyright (c) 2015 Yasser Corrales Morales. All rights reserved.
//

#ifndef __BASE_UTILS__
#define __BASE_UTILS__

#if !defined(__CLING__) || defined(__ROOTCLING__)

#ifndef ROOT_TList
#include <TList.h>
#endif

#ifndef ROOT_Math
#include <TMath.h>
#endif

#ifndef ROOT_Varargs
#include <Varargs.h>
#endif

#endif

#include <iostream>
#include <string>
#include <memory>

using std::string;

namespace BaseUtils
{

#define MyAssert(exp)                                                                           \
  {                                                                                             \
    if ( ! (exp) )                                                                              \
    {                                                                                           \
      cout << "Assert (" << #exp << ") failed at " << __FILE__ << " line " << __LINE__ << endl; \
      exit(1);                                                                                  \
    }                                                                                           \
  }                                                                                             \

  namespace color_txt
  {
    const char c_red[]     =  { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
    const char c_green[]   =  { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    const char c_yellow[]  =  { 0x1b, '[', '1', ';', '3', '3', 'm', 0 };
    const char c_blue[]    =  { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    const char c_magenta[] =  { 0x1b, '[', '1', ';', '3', '5', 'm', 0 };
    const char c_cyan[]    =  { 0x1b, '[', '1', ';', '3', '6', 'm', 0 };
    const char c_frg[]     =  { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
  }; //end color_txt

  namespace
  {
    constexpr UInt_t kMyColors = 15;
    constexpr UInt_t fgMyColor[kMyColors] =
    {
      kBlack,
      kRed,
      kGreen,
      kBlue,
      kYellow + 1,
      kMagenta,
      kCyan,
      kOrange,
      kPink,
      kGreen   + 3,
      kViolet + 10,
      kRed + 3,
      kGray,
      kAzure + 2,
      kGreen + 3
    };  // end constexpr UInt_t fgMyColor

    string str_fmt(const char* va_(fmt), ...)
    {
      va_list args, args_cp;
      va_start (args, va_(fmt));
      va_copy (args_cp, args);
      size_t size = vsnprintf( nullptr, 0, fmt, args ) + 1; // Extra space for '\0'
      std::unique_ptr<char[]> buf( new char[ size ] );
      vsnprintf( buf.get(), size, fmt, args_cp );
      va_end (args);
      va_end (args_cp);
      return string( buf.get(), buf.get() + size - 1 ); // We not want \0
    }  // end string str_fmt...

  };  // end namespace

  void Print()
  {
    std::cout << "Macro with base namespace utils" << std::endl;
    std::cout << "-- namespace color_txt: define color used in the text format" << std::endl;
    std::cout << "-- namespace io: define template for i/o files handling"      << std::endl;
    std::cout << "\t void Requires(T* obj, std::string msg)"                    << std::endl;
    std::cout << "\t void Get(T*& dest, L* from, string name)"                  << std::endl;
    std::cout << "\t void Get(T*& dest, L& from, string name)"                  << std::endl;
    std::cout << "\t void Get(T*& dest, TList* from, string name)"              << std::endl;
    std::cout << "\t s_pnt(double __v, double __e)"                             << std::endl;
  }  // end Print

  const char*  GetAxisTitle_p()    { return "#it{p} (GeV/#it{c})";                                 }
  const char*  GetAxisTitle_pt()   { return "#it{p}_{T} (Gev/#it{c})";                             }
  const char*  GetAxisTitle_dEdx() { return "ITS d#it{E}/d#it{x} (keV/300#scale[0.6]{ }#mum)";     }
  UInt_t GetMyColor(UInt_t index)  { return (index < kMyColors) ? fgMyColor[index] : fgMyColor[0]; }

  template<typename... Args> void PrintMsg(const char* fmt, Args... args)
  {
    Printf("%s%s%s", color_txt::c_green, str_fmt(fmt, args ...).c_str(), color_txt::c_frg);
  }

  void InfoMsg(const char* location, const char* va_(fmt), ...)
  {
    if ( gErrorIgnoreLevel <= kInfo )
    {
      Printf ( "%s", color_txt::c_green );
      va_list ap;
      va_start ( ap, va_(fmt) );
      ErrorHandler ( kInfo, location, va_(fmt), ap );
      va_end (ap);
      Printf ( "%s", color_txt::c_frg );
    }
  }  // end InfoMsg

  void WarnMsg(const char* location, const char* va_(fmt), ...)
  {
    if ( gErrorIgnoreLevel <= kWarning )
    {
      Printf ( "%s", color_txt::c_yellow );
      va_list ap;
      va_start ( ap, fmt );
      ErrorHandler ( kWarning, location, va_(fmt), ap );
      va_end (ap);
      Printf ( "%s", color_txt::c_frg );
    }
  }  // end WarnMsg

  void ErrorMsg(const char* location, const char* va_(fmt), ...)
  {
    if ( gErrorIgnoreLevel <= kError )
    {
      Printf( "%s", color_txt::c_red );
      va_list ap;
      va_start ( ap, va_(fmt) );
      ErrorHandler ( kError, location, va_(fmt), ap );
      va_end ( ap );
      Printf( "%s", color_txt::c_frg );
    }
  }

  template<class T> void Requires(T* obj, std::string msg = "")
  {
    if ( ! obj )
    {
      std::cout << "Missing object \"" << msg.data() << "\". Aborting." << std::endl;
      abort();
    }
  }

  template<typename T, typename L> void Get(T*& dest, L* from, string name)
  {
    dest = static_cast<T*> ( from->Get( name.data() ) );
    Requires ( dest, name );
  }

  template<typename T, typename L> void Get(T*& dest, L& from, string name)
  {
    Get( dest, &from, name );
  }

  template<typename T> void Get(T*& dest, TList* from, string name)
  {
    dest = static_cast<T*> ( from->FindObject( name.data() ) );
    Requires ( dest, name );
  }

  typedef struct s_pnt
  {
    double val;
    double err;

    s_pnt(double __v, double __e):val(__v),err(__e){};
    s_pnt& operator/(const s_pnt& __den)
    {
      err = val/__den.val*TMath::Sqrt(err*err/val/val + __den.err*__den.err/__den.val/__den.val);
      val /= __den.val;
      return *this;
    }
  } t_pnt;

  t_pnt DividePnts(t_pnt& __p_num, t_pnt& __p_den)
  {
    return __p_num/__p_den;
  }
}; //end BaseUtils

#endif /* defined(__BASE_UTILS_) */

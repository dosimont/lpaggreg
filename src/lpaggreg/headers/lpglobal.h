#ifndef LPGLOBAL_H
#define LPGLOBAL_H

//options

#define LP_PRECISION 0.0000000000001

//P values

#define P_MIN 0
#define P_MAX 1
#define P_OPT 2

//#define PARTITION_COMPARE_QUALITY

typedef long double lp_quality_type;

//macros

#define SIZE1 (values.size())
#define SIZE2 (values.size()>0?values.operator [](0).size():0)
#define SIZE3 (values.size()>0&&values.operator [](0).size()>0?values.operator [](0).operator [](0).size():0)
#define SIZE4 (values.size()>0&&values.operator [](0).size()>0&&values.operator [](0).operator [](0).size()?values.operator [](0).operator [](0).operator [](0).size():0)

#endif // LPGLOBAL_H

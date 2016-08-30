#ifndef LPGLOBAL_H
#define LPGLOBAL_H

#define LP_PRECISION 0.0000000000001

//#define PARTITION_COMPARE_QUALITY

typedef long double lp_quality_type;



#define SIZE1 (values.size())
#define SIZE2 (values.size()>0?values.operator [](0).size():0)
#define SIZE3 (values.size()>0&&values.operator [](0).size()>0?values.operator [](0).operator [](0).size():0)
#define SIZE4 (values.size()>0&&values.operator [](0).size()>0&&values.operator [](0).operator [](0).size()?values.operator [](0).operator [](0).operator [](0).size():0)




#endif // LPGLOBAL_H

#include "dpartition.h"

lpaggreg::DPart::DPart(int h, int hsize, int start, int end)
{

}

bool lpaggreg::operator==(lpaggreg::DPart &dpart1, lpaggreg::DPart &dpart2)
{
    return dpart1.getStart()==dpart2.getStart()&&dpart1.getEnd()==dpart2.getEnd()&&dpart1.getH()==dpart2.getH()&&dpart1.getSize()==dpart2.getSize();
}

bool lpaggreg::operator!=(lpaggreg::DPart &dpart1, lpaggreg::DPart &dpart2)
{
    return !(dpart1==dpart2);
}

int lpaggreg::DPart::getH() const
{
    return h;
}

int lpaggreg::DPart::getHSize() const
{
    return hsize;
}

int lpaggreg::DPart::getOSize()
{
    return start-end+1;
}

int lpaggreg::DPart::getStart() const
{
    return start;
}

int lpaggreg::DPart::getEnd() const
{
    return end;
}

int lpaggreg::DPart::getSize()
{
    return hsize*getOSize();
}

lpaggreg::DPartition::DPartition(vector<shared_ptr<UpperTriangularMatrix<int> > > cuts, dqualities qualities, float parameter, lpaggreg::HValuesMetaData metaData):Partition(parameter), cuts(cuts), qualities(qualities), metaData(metaData)
{
    computeParts();
    computeQuality();
}

void lpaggreg::DPartition::computeParts()
{
    parts.clear();
    int h;
    h=metaData.getRoot();
    int i=0;
    int j=((*qualities)[0])->getSize()-1;
    computeSubPart(h, i, j);
}

void lpaggreg::DPartition::computeSubPart(int h, int i, int j){
    int cut=(*(cuts[h]))(i, j);
    if (cut==-1){
        for (int k; i<metaData.getChildren().operator [](h).size(); k++){
            int child=metaData.getChildren().operator [](h).operator [](k);
            computeSubPart(child, i, j);
        }
    }else{
        parts.push_back(DPart(h, (metaData.getSize())[h], i, cut));
        if (cut<j){
            computeSubPart(h, cut+1, j);
        }
    }
}


void lpaggreg::DPartition::computeQuality()
{
    for (DPart it: parts){
        *quality+=*(*(*qualities)[it.getH()])(it.getStart(), it.getEnd());
    }
}

vector<shared_ptr<lpaggreg::UpperTriangularMatrix<int> > > lpaggreg::DPartition::getCuts() const
{
    return cuts;
}

lpaggreg::HValuesMetaData lpaggreg::DPartition::getMetaData() const
{
    return metaData;
}

dqualities lpaggreg::DPartition::getQualities() const
{
    return qualities;
}

vector<lpaggreg::DPart> lpaggreg::DPartition::getParts() const
{
    return parts;
}

bool lpaggreg::operator==(lpaggreg::DPartition &dpartition1, lpaggreg::DPartition &dpartition2)
{
    if (dpartition1.getParts().size()!=dpartition2.getParts().size()){
        return false;
    }else{
        for (int i=0; i<dpartition1.getParts().size(); i++){
            if ((dpartition1.getParts())[i]!=(dpartition2.getParts())[i]){
                return false;
            }
        }
        return true;
    }
}

#ifdef PARTITION_COMPARE_QUALITY
bool lpaggreg::operator==(lpaggreg::DPartition &dpartition1, lpaggreg::DPartition &dpartition2)
{
    return (dpartition1.getQuality()==dpartition2.getQuality());
}
#endif

bool lpaggreg::operator!=(lpaggreg::DPartition &dpartition1, lpaggreg::DPartition &dpartition2)
{
    return !(dpartition1==dpartition2);
}

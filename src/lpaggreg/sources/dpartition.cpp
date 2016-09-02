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

lpaggreg::DPartition::DPartition(vector<vector<int> > cuts, dqualities qualities, float parameter, lpaggreg::HValuesMetaData metaData):Partition(parameter), cuts(cuts), qualities(qualities), metaData(metaData)
{
    computeParts();
    computeQuality();
}

void lpaggreg::DPartition::computeParts()
{
    parts.clear();
    int h;
    for (h=0; h<metaData.getHsize(); h++){
        parts.push_back(vector<DPart>());
    }
    int i=metaData.getHsize()-1;
    for (int h = (metaData.getPath())[i]; i >= 0; h = (metaData.getPath())[--i]){
        for (int j=0; j<(cuts[h]).size();){
            if (cuts[h][j]>=0){
                parts[h].push_back(DPart(h, (metaData.getSize())[h], j, cuts[h][j]));
                for (int child:(metaData.getLeaves())[h]){
                    for (int k=j; k<=cuts[h][j];k++){
                        cuts[child][k]=-2;
                    }
                }
                j=cuts[h][j]+1;
            }else if(cuts[h][j]==-2){
                for (int child:(metaData.getLeaves())[h]){
                    cuts[child][j]=-2;
                }
                j++;
            }else{
                j++;
            }
        }
    }
}


void lpaggreg::DPartition::computeQuality()
{
    for (int h=0; h<metaData.getHsize(); h++){
        for (DPart it: parts[h]){
            *quality+=*(*(*qualities)[h])(it.getStart(), it.getEnd());
        }
    }
}

lpaggreg::HValuesMetaData lpaggreg::DPartition::getMetaData() const
{
    return metaData;
}

dqualities lpaggreg::DPartition::getQualities() const
{
    return qualities;
}

vector<vector<lpaggreg::DPart> > lpaggreg::DPartition::getParts() const
{
    return parts;
}

vector<vector<int> > lpaggreg::DPartition::getCuts() const
{
    return cuts;
}

bool lpaggreg::operator==(lpaggreg::DPartition &dpartition1, lpaggreg::DPartition &dpartition2)
{
    for (int h=0; h<dpartition1.getMetaData().getHsize(); h++){
        if (((dpartition1.getParts())[h]).size()!=((dpartition2.getParts())[h]).size()){
            return false;
        }
        for (int i=0; i<((dpartition1.getParts())[h]).size(); i++){
            if ((dpartition1.getParts())[h][i]!=(dpartition2.getParts())[h][i]){
                return false;
            }
        }
    }
    return true;
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

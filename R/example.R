rm(list=ls())

lpaggreg_location="/opt/ptools/lpaggreg";
source("lpaggreg.R", echo=TRUE, local=TRUE)

#Synthetic example: 2 processes, 2 types, 5 timeslices (keep the same order)
testArray = array(dim=c(2,2,5))
testArray[1,1,] = c(0.5, 0.2, 0.0, 0.1, 0.4)
testArray[1,2,] = c(0.5, 0.8, 1.0, 0.9, 0.6)
testArray[2,1,] = c(0.4, 0.3, 0.1, 0.2, 0.3)
testArray[2,2,] = c(0.6, 0.7, 0.9, 0.8, 0.7)
print(testArray)

#Threshold: 0<th<1, lower value means more accuracy for retrieving the list of partitions but longer computation time
th=0.001

#Temporal aggregation
#Output: a 2D matrix (n,3) with the list of time parts for each parameter
#Columns: parameter p, start timeslice, end timeslice
oaggregate(testArray, th)

#Spatial aggregation
#define hierarchy: vector[index]= index's father index; vector[index]0 means index=root
h=c(3,3,0)
#Output: a 2D matrix (n,3) with the list of aggregate nodes
#Columns: parameter p, node, size
haggregate(testArray, h, th)

#Spatiotemporal aggregation
#Output: a 2D matrix (n,5) with the list of aggregate nodes/time parts
#Columns: parameter p, node, size, start, end
daggregate(testArray, h, th)

color_generator_Clusters <- function(stringlist, aggString=c("")){
  colors=rep("black", length(stringlist))
  names(colors)=stringlist
  colors["Cluster 1"]="green"
  colors["Cluster 2"]="yellow"
  colors["Cluster 3"]="red"
  colors["Cluster 4"]="darkgreen"
  colors["Cluster 5"]="deeppink"
  colors["Cluster 6"]="darkviolet"
  colors["Cluster 7"]="darkkhaki"
  colors["Cluster 8"]="orange"
  colors["Cluster 9"]="cyan"
  colors["Cluster 10"]="darkolivegreen"
  colors["Cluster 11"]="orchid"
  colors["Duration Filtered"]="black"
  colors["Noise"]="grey"
  names(colors)=stringlist
  colors
}


#Real trace example
trace=parsepjdump("nemo.exe.128tasks.chop1.clustered.pjdump")

trace$data<-trace$data[!(trace$data$Value %in% c('Duration Filtered','Noise')),]

micro=pjdump2microstate(trace,20)

#Aggregations
odf<-oaggregate(micro$data, th)
hdf<-haggregate(micro$data, micro$hierarchy, th)
#ddf<-daggregate(micro$data, micro$hierarchy, th)

#Printing the algorithm output
odf
hdf
#head(ddf)

#Generating a plot for a randomly chosen parameter
oplot(omacro(odf, micro, unique(odf$Parameter)[2]), color_generator_Clusters)

hplot(hmacro(hdf, micro, unique(hdf$Parameter)[8]), color_generator_Clusters)

#Without hierarchy
trace=parsepjdump("cholesky_11520_960_starpu_25_3_dmda_1_idcin-2.grenoble.grid5000.fr_2016-08-21_20-49-12_pjdump.csv")

#Example of filtering
trace$data<-trace$data[!(trace$data$Value %in% c('Idle','Sleeping')),]

#No hierarchy (because it's not present in the trace, but it should be...)
micro=pjdump2microstate(trace,50,FALSE)

odf<-oaggregate(micro$data, th)

odf

oplot(omacro(odf, micro, unique(odf$Parameter)[4]))

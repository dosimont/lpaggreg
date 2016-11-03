library(sqldf)
library(dplyr)

factor2numeric <- function(f)
{
  if(!is.factor(f)) stop("the input must be a factor")
  as.numeric(levels(f))[as.integer(f)]
}

slicer <- function (trace, timeSliceNumber)
{
  start <- min(trace$Start)
  trace$Start <- trace$Start - start
  trace$End <- trace$End - start
  maxts <- max(trace$End)
  slicets = maxts/timeSliceNumber;
  slices <- data.frame(SliceId=1:timeSliceNumber, TsStart=(0:(timeSliceNumber-1))*slicets, TsEnd=(1:timeSliceNumber)*slicets);
  h <- sqldf('SELECT trace.ResourceId, trace.Start, trace.End, trace.Duration, trace.Value, slices.SliceId, slices.TsStart, slices.TsEnd
             FROM trace
             INNER JOIN slices
             ON (trace.Start+trace.Duration > slices.TsStart) AND (trace.End-trace.Duration < slices.TsEnd)')
  h$Duration <- NULL;
  m <- h %>% group_by(ResourceId, Start, End, SliceId, Value) %>%
    mutate(N=n(), TinTS = (min(End,TsEnd) - max(Start,TsStart))) %>%
    group_by(ResourceId, SliceId, Value, TsStart, TsEnd) %>%
    summarize (Sum=sum(TinTS), Normalized=Sum/slicets) %>%
    as.data.frame();
  p <- expand.grid(ResourceId=unique(m$ResourceId), SliceId = 1:max(m$SliceId), Value = unique(m$Value));
  p$TsStart = 0;
  p$TsEnd = 0;
  p$Sum = 0;
  p$Normalized = 0;
  n <- rbind(p, m);
  o <- n %>% group_by (ResourceId, SliceId, Value) %>%
    summarize(TsStart = max(TsStart), TsEnd = max(TsEnd), Sum = max(Sum), Normalized=max(Normalized)) %>% as.data.frame;
  return (o);
}


parsePJDump <- function (file, timeSliceNumber){
  
  names <- c("Nature", "ResourceId", "Type", "Start", "End", "Duration", "Depth", "Value", "a", "b", "c", "d", "e", "f", "g")
  trace <- read.table(file, sep=",", fill=TRUE, header=FALSE, col.names=names)
  
  trace$a <- NULL
  trace$b <- NULL
  trace$c <- NULL
  trace$d <- NULL
  trace$e <- NULL
  trace$f <- NULL
  trace$g <- NULL
  
  resources <- trace[trace$Nature %in% "Container",]
  resources$Nature <- NULL
  resources$Type <- NULL
  resources$Start <- NULL
  resources$End <- NULL
  resources$Duration <- NULL
  resources$Value <- NULL
  resources$ParentId <- resources$ResourceId
  resources$ResourceId <- resources$Depth
  resources$Depth <- NULL
  
  #does not work, why???
  resources <- resources[!(resources$ResourceId %in% '0'),]
  
  subtrace <- trace[trace$Nature %in% "State",]
  
  #carefull, for spatial, only leaves should produce values!
  df <- slicer(subtrace, timeSliceNumber)
  
  time <- unique(df$SliceId)
  time <- time[order(time)]
  
  value <- unique(df$Value)
  value <- value[order(value)]
  
  parents <- unique(resources$ParentId)
  parents<-parents[order(parents)]
  parents<-rev(parents)
  
  #remove parents from df
  df <- df[!(df$ResourceId %in% parents),]
  
  space <- unique(df$ResourceId)
  space <- space[order(space)]
  
  hierarchy <- factor(c(as.character(space),as.character(parents)))
  hierarchy<-unique(hierarchy)
  hierarchy.name=as.character(hierarchy)
  resources$ParentIndex=-1
  vhierarchy <- rep(-1,length(hierarchy))
  vhierarchy.name=as.character(hierarchy)
  
  for (i in 1:length(vhierarchy)){
    resources[resources$ResourceId %in% hierarchy[i],"ParentIndex"]=match(resources[resources$ResourceId %in% hierarchy[i],"ParentId"],hierarchy)[1]
  }
  resources[1,"ParentIndex"]=0
  for (i in 1:length(vhierarchy)){
    vhierarchy[i]=resources[resources$ResourceId %in% hierarchy[i],"ParentIndex"]
  }
  
  dataCube <- array(0,
                    dim = c(length(space), length(value), length(time)),
                    dimnames = list("space"=space, "value"=value, "time"=time)
  )
  
  for (r in 1:nrow(df)) {
    row <- df[r,]
    dataCube[as.character(row$ResourceId),as.character(row$Value),as.character(row$SliceId)] <- row$Normalized
  }
  ret<-list("data"=dataCube,"hierarchy"=vhierarchy)
  ret
}
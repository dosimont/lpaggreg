source("functions.R")
library(sets)

parsePJDump <- function (file, timeSliceNumber){

trace <- read.table(file, sep=",", fill=TRUE, header=TRUE)

trace

subtrace <- trace[trace$Depth == 0,]
space <- unique(subtrace$ResourceId)
space <- space[order(space)]
subtrace <- subtrace[subtrace$ResourceId %in% space,]

stepNb <- timeSliceNumber
start <- min(subtrace$Start)
end <- max(subtrace$End)
step <- (end-start)/stepNb
time <- seq(start,end-step,step)

value <- unique(subtrace$Value)
value <- value[order(value)]

dataCube <- array(0,
                  dim = c(length(space), length(value), length(time)),
                  dimnames = list("space"=space, "value"=value, "time"=time)
)

for (r in 1:nrow(subtrace)) {
  row <- subtrace[r,]
  for (t in time) {
    interval <- interval_intersection(interval(row$Start,row$End),interval(t,t+step))
    size <- 0
    if (!interval_is_empty(interval)) { size <- max(interval) - min(interval) }
    dataCube[as.character(row$ResourceId),as.character(row$Value),as.character(t)] <- dataCube[as.character(row$ResourceId),as.character(row$Value),as.character(t)] + size/step
  }
}

dataCube
}

#ifndef MODEL_AIQ_H
#define MODEL_AIQ_H

//column numbers for measurements in serial data - add 1 if logging (check if logging by checking for decimal place in column 1)
#define OZONE_COLUMN 0
#define TEMPERATURE_COLUMN 1
#define PRESSURE_COLUMN 2
#define FLOW_COLUMN 3
#define TIME_COLUMN 5
#define DATE_COLUMN 4
#define LOGGING_OFFSET 1        //add this if logging

#define NUMBER_OF_COLUMNS 6

#endif // MODEL_AIQ_H

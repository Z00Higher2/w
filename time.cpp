// Author: Zuhayer Tashin
// Course: CSCI-135
// Instructor: Tong Yi
// Assignment: Lab 10A
//Add a new function
// bool timeOverlap(TimeSlot ts1, TimeSlot ts2); 
// The function should return true if the two time slots overlap, otherwise return false. 
// (Take into account the starting times of the time slots and the duration of the scheduled movies.)
// Hint: You may use minutesUntil to check which time slot is earlier, then find the how long is the interval between their starting times.
// They overlap if the movie duration is greater than the interval between the time slots’ starting times. 
// Alternatively, converting times into minutes since midnight can be a good idea as well.
// (By the way, if you want to be accurate, if one movie starts at 10:00 and lasts 90 minutes until 11:30, 
// then it does not overlap with a movie that starts exactly at 11:30. 
// However, they would overlap if the latter movie started one minute earlier, at 11:29.)

#include <iostream>
#include <string>
using namespace std;

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

class Time { 
public:
    int h;
    int m;
};

class Movie { 
public: 
    string title;
    Genre genre;     // only one genre per movie
    int duration;    // in minutes
};

class TimeSlot { 
public: 
    Movie movie;     // what movie
    Time startTime;  // when it starts
};

int minutesUntil(Time earlier, Time later){
    int difference_minutes = later.m - earlier.m;
    int difference_hours = later.h - earlier.h;

    int total = difference_hours * 60;
    int total_minutes = total + difference_minutes;
    cout << total_minutes << endl;
    return total_minutes; // returns the total minutes
}

Time addMinutes(Time time0, int min){
    Time time = time0;
    int minutes = min;
    while (minutes >= 60) {
        // If minutes is 60 or more, we need to adjust the time
        time.h += 1;    // Increment the hour by 1
        minutes -= 60;  // Subtract 60 minutes from the total
    }

        // Adding the remaining minutes to the current time
    time.m += minutes;

    // If minutes exceed 60, adjust hours accordingly
    if (time.m >= 60) {
        time.h += 1;    // Increment the hour by 1
        time.m -= 60;   // Subtract 60 minutes
    }

    return time;

}

void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

void printTimeSlot(TimeSlot ts){
    printMovie(ts.movie);
    cout << " [ starts at "<< ts.startTime.h << ":" <<  ts.startTime.m <<", ends by ";
    ts.startTime = addMinutes({ts.startTime.h, ts.startTime.m}, ts.movie.duration); // Updates the start time of the movie which will be the end time of the movie
    cout << ts.startTime.h << ":" << ts.startTime.m <<  " ]" << endl;
    

}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
 // Check if the start times have the same hour and minute
    if (ts1.startTime.h == ts2.startTime.h && ts1.startTime.m == ts2.startTime.m) {
        return true; // Overlap
    }

    // Calculate end times
    Time endTime1 = addMinutes(ts1.startTime, ts1.movie.duration);
    Time endTime2 = addMinutes(ts2.startTime, ts2.movie.duration);

    // Check for overlap
    if ((ts1.startTime.h < endTime2.h || (ts1.startTime.h == endTime2.h && ts1.startTime.m < endTime2.m)) &&
        (ts2.startTime.h < endTime1.h || (ts2.startTime.h == endTime1.h && ts2.startTime.m < endTime1.m))) {
        return true; // Overlap
    }

    return false; // No overlap
}



int main(){
    Movie movie1 = {"Back to the Future", COMEDY, 116};
    Movie movie2 = {"Black Panther", ACTION, 134};

    TimeSlot morning = {movie1, {9, 15}};  
    TimeSlot daytime = {movie2, {10, 00}}; 
    TimeSlot evening = {movie2, {16, 45}};
    TimeSlot evening2 = {movie2, {19, 15}};
    TimeSlot night = {movie1, {21, 35}};

    cout << timeOverlap({{"The Wolf of Wall Street", COMEDY, 180}, {10, 30}}, {{"5 Centimeters Per Second", DRAMA, 63}, {10, 30}}) << endl;

        
    return 0; 


}
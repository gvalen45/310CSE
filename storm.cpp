/*
 *
 * Gabriel Valenzuela
 * CSE 310
 * Project 2 - Weather
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include <iostream>
#include "defnsACTUAL.h"
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <cmath>
#include <sstream>


using namespace std;
bool boolFlag = false;
bool isPrime(int n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;

    return true;
}

string removeQuotes(string strFromChar){
    string newStr = "";
    int pos = 0;
    while ((pos = strFromChar.find('"', pos)) != std::string::npos){
        newStr = strFromChar.erase(pos, 1);
    }//
    return newStr;
}
int nextPrime(int N)
{

    // Base case
    if (N <= 1)
        return 2;

    int prime = N;
    bool found = false;

    // true for a number greater than n
    while (!found) {
        prime++;

        if (isPrime(prime))
            found = true;
    }

    return prime;
}
//Found on Geeks for Geeks

int convertStringToInt(const string& s){
    stringstream stringNum(s);
    int x = 0;
    stringNum >> x;
    return  x;
}

int returnMoneyInt(const string& s){

    char u = s[s.length()-1];
    float add;
    int x;
    if (u == '0'){
        add = 0;
    }
    else{
        string s_sub = s.substr(0,s.length()-1);
        add = strtof(s_sub.c_str(),NULL);
       //gets 1000
        if (u == 'K'){
            add = add*1000;
        }
        //gets 1000000
        else if (u == 'M'){
            add = add*1000000;
        }
    }
    x = int(add);
    return  x;
}



int compare_state(char* s1, char* s2){
    int idx=0;
    int result;
    if (int(s1[idx])<=int (s2[idx])){
        result = 0;
        return result;
    }
    else if (int(s1[idx])>int (s2[idx])){
        result = 1;
        return result;
    }
}

void build_fatalities_structure(fstream& file_F_1, struct fatality_event *fatality_event_save ,int file_size_F){
    string line;
    getline ( file_F_1, line); // read a string
//    fatality_event fatality_event_save[file_size_F]; // save fatality information
    for (int i=0; i<file_size_F; i++){
        getline ( file_F_1, line, ',');
        fatality_event_save[i].fatality_id = convertStringToInt(line);
        getline ( file_F_1, line, ',');
        fatality_event_save[i].event_id = convertStringToInt(line);
        getline ( file_F_1, line, ',');
        fatality_event_save[i].fatality_type = line[0];
        getline(file_F_1, line, ',');
        strcpy(fatality_event_save[i].fatality_date, line.c_str());
        if (char(file_F_1.peek())==','){
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_age = 0;
        }
        else{
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_age = convertStringToInt(line);
        }
        if (char(file_F_1.peek())==','){
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_sex = ' ';
        }
        else{
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_sex = line[0];
        }
        getline(file_F_1, line, '\n');
        if (line.length()>1) {
            strcpy(fatality_event_save[i].fatality_location, line.c_str());
        }
        else {
            string tem = " ";
            strcpy(fatality_event_save[i].fatality_location, tem.c_str());
        }
        fatality_event_save[i].next = NULL;
    }
//    for (int i=0; i<file_size_F; i++){
//        cout << fatality_event_save[i].fatality_id << " " << fatality_event_save[i].event_id<< endl;
//    }
}

int cMonth(char* s1, char* s2){
    int result = strcmp(s1, s2);
    if (result==0){
        return result;
    }
    else{
        int idx=0;
        while(int(s1[idx])==int (s2[idx])){
            idx++;
        }
        if (int(s1[idx])<int (s2[idx])){
            result=0;
            return result;
        }
        else if (int(s1[idx])>int (s2[idx])){
            result=1;
            return result;
        }
    }
}
void buildEventStruct(fstream& file_1, struct storm_event *storm_event_save ,int file_size,
                           struct fatality_event *fatality_event_save, int file_size_F){
    string value;
    getline ( file_1, value); // read a string
    for (int i=0; i<file_size; i++){ // save storm event into an array struct
        getline ( file_1, value,',');
        storm_event_save[i].event_id = convertStringToInt(value);
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].state, value.c_str());
        getline ( file_1, value,',');
        storm_event_save[i].year = convertStringToInt(value);
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].month_name, value.c_str());
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].event_type, value.c_str());
        getline ( file_1, value,',');
        storm_event_save[i].cz_type= value[0];
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].cz_name, value.c_str());
        getline ( file_1, value,',');
        storm_event_save[i].injuries_direct = convertStringToInt(value);
        getline ( file_1, value,',');
        storm_event_save[i].injuries_indirect = convertStringToInt(value);
        getline ( file_1, value,',');
        storm_event_save[i].deaths_direct = convertStringToInt(value);
        getline ( file_1, value,',');
        storm_event_save[i].deaths_indirect = convertStringToInt(value);
        if (char(file_1.peek())==','){
            // empty cell
            getline(file_1, value, ',');
            storm_event_save[i].damage_property = 0;
        }
        else{
            getline ( file_1, value,',');
            storm_event_save[i].damage_property = returnMoneyInt(value);
        }
        if (char(file_1.peek())==','){
            // empty cell
            getline(file_1, value, ',');
            storm_event_save[i].damage_crops = 0;
        }
        else{
            getline ( file_1, value,',');
            storm_event_save[i].damage_crops = returnMoneyInt(value);
        }
        getline ( file_1, value,'\n');
        if (value.length()>1){
            //strcpy(storm_event_save[i].tor_f_scale, value.c_str());
        }
        else{
            string next_value = "N/A";
            //strcpy(storm_event_save[i].tor_f_scale, next_value.c_str());
        }
        storm_event_save[i].f =NULL;

        for (int j=0; j<file_size_F; j++){
            if (fatality_event_save[j].event_id == storm_event_save[i].event_id){
                struct fatality_event * tempVal = storm_event_save[i].f;
                struct fatality_event * head = storm_event_save[i].f;
                if (tempVal == NULL){
                    tempVal = new fatality_event;
                    tempVal->fatality_id = fatality_event_save[j].fatality_id;
                    tempVal->event_id = fatality_event_save[j].event_id;
                    tempVal->fatality_type = fatality_event_save[j].fatality_type;
                    strcpy(tempVal->fatality_date, fatality_event_save[j].fatality_date);
                    tempVal->fatality_age = fatality_event_save[j].fatality_age;
                    tempVal->fatality_sex = fatality_event_save[j].fatality_sex;
                    strcpy(tempVal->fatality_location, fatality_event_save[j].fatality_location);
                    tempVal->next = NULL;
                    storm_event_save[i].f = tempVal;

                    
                }
                else{
                    
                    tempVal = new fatality_event;
                    tempVal->fatality_id = fatality_event_save[j].fatality_id;
                    tempVal->event_id = fatality_event_save[j].event_id;
                    tempVal->fatality_type = fatality_event_save[j].fatality_type;
                    strcpy(tempVal->fatality_date, fatality_event_save[j].fatality_date);
                    tempVal->fatality_age = fatality_event_save[j].fatality_age;
                    tempVal->fatality_sex = fatality_event_save[j].fatality_sex;
                    strcpy(tempVal->fatality_location, fatality_event_save[j].fatality_location);
                    tempVal-> next = head;
                    storm_event_save[i].f = tempVal;

                }
            }
        }
    }
//    for (int i=0; i<file_size;i++){
//        cout<< "Hi " << storm_event_save[i].event_id <<endl;
//    }
//    cout<< "Hi" << endl;
}


int hash_fun(int hash_size, int key){
    return key%hash_size;
}
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void  build_hash_table(struct hash_table_entry **t, int hash_size, int file_size, struct storm_event *storm_event_save){
    int key;
    for (int i = 0; i<file_size; i++){
        key = hash_fun(hash_size,storm_event_save[i].event_id);
//        cout << "Key "<< key << endl;

        struct hash_table_entry* pEntry = t[key];
        struct hash_table_entry* temp = t[key];
//        cout << en<< endl;
        if (pEntry == NULL){
            pEntry = new hash_table_entry;
            pEntry->event_id = storm_event_save[i].event_id;
            pEntry->year = storm_event_save[i].year;
            pEntry->event_index = i;
            pEntry->next = NULL;
            t[key] = pEntry;
        }
        else{
            pEntry = new hash_table_entry;
            pEntry->event_id = storm_event_save[i].event_id;
            pEntry->year = storm_event_save[i].year;
            pEntry->event_index = i;
            pEntry->next = temp;
            t[key] = pEntry;
//            cout << "here "<< t[key]<< endl;
        }
    }
}



void max_heapify_property(struct storm_event *all_event_save, int i, int file_size){
    int l;
    int r;
    int largest=i;
    l = 2*i+1;
    r = 2*i+2;
    if (l<file_size && all_event_save[l].damage_property>all_event_save[i].damage_property){
        largest = l;
    }
    if (r<file_size && all_event_save[r].damage_property>all_event_save[i].damage_property){
        largest = r;
    }
    if (largest!=i){
        struct storm_event * temp = new storm_event;
        temp->event_id = all_event_save[i].event_id;
        strcpy(temp->state, all_event_save[i].state);
        temp->year = all_event_save[i].year;
        strcpy (temp->month_name, all_event_save[i].month_name);
        strcpy(temp->event_type, all_event_save[i].event_type);
        temp->cz_type = all_event_save[i].cz_type;
        strcpy(temp->cz_name, all_event_save[i].cz_name);
        temp->injuries_direct = all_event_save[i].injuries_direct;
        temp->injuries_indirect = all_event_save[i].injuries_indirect;
        temp->deaths_direct = all_event_save[i].deaths_direct;
        temp->deaths_indirect = all_event_save[i].deaths_indirect;
        temp->damage_property = all_event_save[i].damage_property;
        temp->damage_crops = all_event_save[i].damage_crops;
        //strcpy(temp->tor_f_scale, all_event_save[i].tor_f_scale);
        temp->f = all_event_save[i].f;

        all_event_save[i].event_id = all_event_save[largest].event_id;
        strcpy(all_event_save[i].state, all_event_save[largest].state);
        all_event_save[i].year = all_event_save[largest].year;
        strcpy (all_event_save[i].month_name, all_event_save[largest].month_name);
        strcpy(all_event_save[i].event_type, all_event_save[largest].event_type);
        all_event_save[i].cz_type = all_event_save[largest].cz_type;
        strcpy(all_event_save[i].cz_name, all_event_save[largest].cz_name);
        all_event_save[i].injuries_direct = all_event_save[largest].injuries_direct;
        all_event_save[i].injuries_indirect = all_event_save[largest].injuries_indirect;
        all_event_save[i].deaths_direct = all_event_save[largest].deaths_direct;
        all_event_save[i].deaths_indirect = all_event_save[largest].deaths_indirect;
        all_event_save[i].damage_property = all_event_save[largest].damage_property;
        all_event_save[i].damage_crops = all_event_save[largest].damage_crops;
        //strcpy(all_event_save[i].tor_f_scale, all_event_save[largest].tor_f_scale);
        all_event_save[i].f = all_event_save[largest].f;

        all_event_save[largest].event_id = temp->event_id;
        strcpy( all_event_save[largest].state, temp->state);
        all_event_save[largest].year = temp->year;
        strcpy ( all_event_save[largest].month_name, temp->month_name);
        strcpy( all_event_save[largest].event_type, temp->event_type);
        all_event_save[largest].cz_type = temp->cz_type;
        strcpy( all_event_save[largest].cz_name, temp->cz_name);
        all_event_save[largest].injuries_direct = temp->injuries_direct;
        all_event_save[largest].injuries_indirect = temp->injuries_indirect;
        all_event_save[largest].deaths_direct = temp->deaths_direct;
        all_event_save[largest].deaths_indirect = temp->deaths_indirect;
        all_event_save[largest].damage_property = temp->damage_property;
        all_event_save[largest].damage_crops = temp->damage_crops;
        all_event_save[largest].f = temp->f;
        max_heapify_property(all_event_save, largest, file_size);
    }
}

void max_heapify_crops(struct storm_event *all_event_save, int i, int file_size){
    int l;
    int r;
    int largest = i;
    l = 2*i+1;
    r = 2*i+2;
    if (l<file_size && all_event_save[l].damage_crops>all_event_save[i].damage_crops){
        largest = l;
    }
    if (r<file_size && all_event_save[r].damage_crops>all_event_save[i].damage_crops){
        largest = r;
    }
    if (largest!=i){
        swap(all_event_save[i],all_event_save[largest]);
        max_heapify_crops(all_event_save, largest, file_size);
    }
}

void build_max_heap_property(struct storm_event *all_event_save, int file_size){
    int start = floor(file_size/2);
    for (int i=start; i>=0;i--){
        max_heapify_property(all_event_save, i, file_size);
    }
}

void maxHeapCropsBuild(struct storm_event *all_event_save, int file_size){
    int start = floor(file_size/2);
    for (int i=start; i>=0;i--){
        max_heapify_crops(all_event_save, i, file_size);
    }
}

void max_heapify_fatality(struct max_fatality * max_fatality_save, int i, int file_size){
    int l;
    int r;
    int largest = i;
    l = 2*i+1;
    r = 2*i+2;
    if (l<file_size && max_fatality_save[l].num_fatality>max_fatality_save[i].num_fatality){
        largest = l;
    }
    if (r<file_size && max_fatality_save[r].num_fatality>max_fatality_save[i].num_fatality){
        largest = r;
    }
    if (largest!=i){
        swap( max_fatality_save[i], max_fatality_save[largest]);
        max_heapify_fatality( max_fatality_save, largest, file_size);
    }
}

void build_max_heap_fatality(struct max_fatality * max_fatality_save, int file_size){
    int start = floor(file_size/2);
    for (int i=start; i>=0;i--){
        max_heapify_fatality(max_fatality_save, i, file_size);
    }
}

struct storm_event* delete_max_heap_property(struct storm_event *all_event_save, int file_size){
    file_size = file_size-1;
    storm_event * new_all_event_save = new storm_event[file_size];
    for (int i=0; i<file_size;i++){
        new_all_event_save[i] = all_event_save[i+1];
    }
    return new_all_event_save;
}

struct storm_event* delete_max_heap_crops(struct storm_event *all_event_save, int file_size){
    file_size = file_size-1;
    storm_event * new_all_event_save = new storm_event[file_size];
    for (int i=0; i<file_size;i++){
        new_all_event_save[i] = all_event_save[i+1];
    }
    return new_all_event_save;
}

struct max_fatality* delete_max_heap_fatality(struct max_fatality *all_fatality_save, int file_size){
    file_size = file_size-1;
    max_fatality * new_all_fatality_save = new max_fatality[file_size];
    for (int i=0; i<file_size;i++){
        new_all_fatality_save[i] = all_fatality_save[i+1];
    }
    return new_all_fatality_save;
}

void find_event(struct hash_table_entry **t,int event_id, int hash_size, int num_file, const int year_index[], struct annual_storms * stormsSaved)
        {
    int key;
    key = hash_fun(hash_size,event_id);
    hash_table_entry * Entry = t[key];

    if (Entry != NULL){

        while(Entry != NULL){

            if (Entry->event_id == event_id){
                //declare varibles
                int yyyy = Entry->year;
                int index=0;

                for (int i=0;i<num_file;i++){
                    if (yyyy == year_index[i])
                        index = i;
                }
                cout << "Event ID: " << Entry->event_id << endl;
                cout << "State: " << stormsSaved[index].events[Entry->event_index].state << endl;
                cout << "Year: " << stormsSaved[index].events[Entry->event_index].year << endl;
                cout << "Month Name: " << stormsSaved[index].events[Entry->event_index].month_name << endl;
                cout << "Event Type: " << stormsSaved[index].events[Entry->event_index].event_type << endl;
                    /*cout << "Event ID: " << Entry->event_id << endl;
                    cout << "State: " << stormsSaved[index].events[Entry->event_index].state << endl;
                    cout << "Year: " << stormsSaved[index].events[Entry->event_index].year << endl;
                    cout << "Month Name: " << stormsSaved[index].events[Entry->event_index].month_name << endl;
                    cout << "Event Type: " << stormsSaved[index].events[Entry->event_index].event_type << endl;
                    */cout << "County/Zone Type: " << stormsSaved[index].events[Entry->event_index].cz_type << endl;

                cout << "County/Zone Name: " << stormsSaved[index].events[Entry->event_index].cz_name << endl;
                cout << "Injuries Direct: " << stormsSaved[index].events[Entry->event_index].injuries_direct << endl;
                cout << "Injuries Indirect: " << stormsSaved[index].events[Entry->event_index].injuries_indirect << endl;
                cout << "Deaths Direct: " << stormsSaved[index].events[Entry->event_index].deaths_direct << endl;
                cout << "Deaths Indirect: " << stormsSaved[index].events[Entry->event_index].deaths_indirect << endl;
                cout << "Damage Property: $" << stormsSaved[index].events[Entry->event_index].damage_property << endl;
                cout << "Damage Crops: $" << stormsSaved[index].events[Entry->event_index].damage_crops << endl;
                /*cout << "County/Zone Type: " << stormsSaved[index].events[Entry->event_index].cz_type << endl;
                cout << "County/Zone Name: " << stormsSaved[index].events[Entry->event_index].cz_name << endl;
                cout << "Injuries Direct: " << stormsSaved[index].events[Entry->event_index].injuries_direct << endl;
                cout << "Injuries Indirect: " << stormsSaved[index].events[Entry->event_index].injuries_indirect << endl;
                cout << "Deaths Direct: " << stormsSaved[index].events[Entry->event_index].deaths_direct << endl;
                cout << "Deaths Indirect: " << stormsSaved[index].events[Entry->event_index].deaths_indirect << endl;
                cout << "Damage Property: " << stormsSaved[index].events[Entry->event_index].damage_property << endl;
                cout << "Damage Crops: " << stormsSaved[index].events[Entry->event_index].damage_crops << endl;
                */
                if (stormsSaved[index].events[Entry->event_index].f == NULL){
                    cout <<endl;
                    cout << "\tNo fatalities " << endl;
                }
                else{
                    while (stormsSaved[index].events[Entry->event_index].f != NULL){
                        cout<< endl;
                        cout << "\tFatality ID: " << stormsSaved[index].events[Entry->event_index].f->fatality_id << endl;
                        cout << "\tFatality Type: " << stormsSaved[index].events[Entry->event_index].f->fatality_type << endl;
                        cout << "\tFatality Data: " << stormsSaved[index].events[Entry->event_index].f->fatality_date << endl;
                        cout << "\tFatality Age: " << stormsSaved[index].events[Entry->event_index].f->fatality_age << endl;
                        cout << "\tFatality Sex: " << stormsSaved[index].events[Entry->event_index].f->fatality_sex << endl;
                        cout << "\tFatality Location: " << stormsSaved[index].events[Entry->event_index].f->fatality_location << endl;
                        stormsSaved[index].events[Entry->event_index].f = stormsSaved[index].events[Entry->event_index].f->next;
                        cout << endl;
                    }
                    break;
                }
            }
            Entry = Entry->next;
        }
    }
    else{
        cout<< "There is no such event." << endl;
    }
}
/*void findFatality(struct hash_table_entry **t, int eventId, int hashSize, int num_file,
                  const int year_index[], struct annual_storms * annualStormSavedData){

if (Entry != NULL){

while(Entry != NULL){

if (Entry->event_id == event_id){
//declare varibles
int yyyy = Entry->year;
int index=0;

for (int i=0;i<num_file;i++){
if (yyyy == year_index[i])
index = i;
}
cout << "Event ID: " << Entry->event_id << endl;
cout << "State: " << stormsSaved[index].events[Entry->event_index].state << endl;
cout << "Year: " << stormsSaved[index].events[Entry->event_index].year << endl;
cout << "Month Name: " << stormsSaved[index].events[Entry->event_index].month_name << endl;
cout << "Event Type: " << stormsSaved[index].events[Entry->event_index].event_type << endl;
cout << "Event ID: " << Entry->event_id << endl;
cout << "State: " << stormsSaved[index].events[Entry->event_index].state << endl;
cout << "Year: " << stormsSaved[index].events[Entry->event_index].year << endl;
cout << "Month Name: " << stormsSaved[index].events[Entry->event_index].month_name << endl;
cout << "Event Type: " << stormsSaved[index].events[Entry->event_index].event_type << endl;
cout << "County/Zone Type: " << stormsSaved[index].events[Entry->event_index].cz_type << endl;
cout << "County/Zone Name: " << stormsSaved[index].events[Entry->event_index].cz_name << endl;
cout << "Injuries Direct: " << stormsSaved[index].events[Entry->event_index].injuries_direct << endl;
cout << "Injuries Indirect: " << stormsSaved[index].events[Entry->event_index].injuries_indirect << endl;
cout << "Deaths Direct: " << stormsSaved[index].events[Entry->event_index].deaths_direct << endl;
cout << "Deaths Indirect: " << stormsSaved[index].events[Entry->event_index].deaths_indirect << endl;
cout << "Damage Property: " << stormsSaved[index].events[Entry->event_index].damage_property << endl;
cout << "Damage Crops: " << stormsSaved[index].events[Entry->event_index].damage_crops << endl;
cout << "County/Zone Type: " << stormsSaved[index].events[Entry->event_index].cz_type << endl;
cout << "County/Zone Name: " << stormsSaved[index].events[Entry->event_index].cz_name << endl;
cout << "Injuries Direct: " << stormsSaved[index].events[Entry->event_index].injuries_direct << endl;
cout << "Injuries Indirect: " << stormsSaved[index].events[Entry->event_index].injuries_indirect << endl;
cout << "Deaths Direct: " << stormsSaved[index].events[Entry->event_index].deaths_direct << endl;
cout << "Deaths Indirect: " << stormsSaved[index].events[Entry->event_index].deaths_indirect << endl;
cout << "Damage Property: " << stormsSaved[index].events[Entry->event_index].damage_property << endl;
cout << "Damage Crops: " << stormsSaved[index].events[Entry->event_index].damage_crops << endl;

if (stormsSaved[index].events[Entry->event_index].f == NULL){
cout <<endl;
cout << "\tNo fatalities " << endl;
}
else{
while (stormsSaved[index].events[Entry->event_index].f != NULL){
cout<< endl;
cout << "\tFatality ID: " << stormsSaved[index].events[Entry->event_index].f->fatality_id << endl;
cout << "\tFatality Type: " << stormsSaved[index].events[Entry->event_index].f->fatality_type << endl;
cout << "\tFatality Data: " << stormsSaved[index].events[Entry->event_index].f->fatality_date << endl;
cout << "\tFatality Age: " << stormsSaved[index].events[Entry->event_index].f->fatality_age << endl;
cout << "\tFatality Sex: " << stormsSaved[index].events[Entry->event_index].f->fatality_sex << endl;
cout << "\tFatality Location: " << stormsSaved[index].events[Entry->event_index].f->fatality_location << endl;
stormsSaved[index].events[Entry->event_index].f = stormsSaved[index].events[Entry->event_index].f->next;
cout << endl;
}
break;
}
}
Entry = Entry->next;
}
}

}*/
void findFatality(struct hash_table_entry **t, int eventId, int hashSize, int num_file,
                  const int year_index[], struct annual_storms * annualStormSavedData){
    int key;
    key = hash_fun(hashSize,eventId);
    hash_table_entry * pEntry = t[key];

    if (pEntry != NULL){
        while(pEntry != NULL){
            if ((1*(pEntry->event_id)) == eventId){
                cout << endl;
                // DELETE
                //cout << "The most fatal storm id: " << eventId << endl;
                int yyyy = pEntry->year;
                int index=0;
                for (int i=0;i<num_file;i++){
                    if (yyyy == year_index[i])
                        index = i;
                }
                if (annualStormSavedData[index].events[pEntry->event_index].f == NULL){
                    cout <<endl;

                    cout << "No fatalities " << endl;
                }
                else{
                    while (annualStormSavedData[index].events[pEntry->event_index].f != NULL){
                        cout << "Fatality ID: " << annualStormSavedData[index].events[pEntry->event_index].f->fatality_id << endl;
                        cout << "Event ID: " << annualStormSavedData[index].events[pEntry->event_index].f->event_id << endl;
                        cout << "Fatality Type: " << annualStormSavedData[index].events[pEntry->event_index].f->fatality_type << endl;
                        cout << "fatality Date: " << annualStormSavedData[index].events[pEntry->event_index].f->fatality_date << endl;
                        cout << "Fatality Age: " << annualStormSavedData[index].events[pEntry->event_index].f->fatality_age << endl;
                        cout << "Fatality Sex: " << annualStormSavedData[index].events[pEntry->event_index].f->fatality_sex << endl;
                        cout << "Fatality Location: " << annualStormSavedData[index].events[pEntry->event_index].f->fatality_location << endl;
                        cout << endl;
                        annualStormSavedData[index].events[pEntry->event_index].f =
                                annualStormSavedData[index].events[pEntry->event_index].f->next;
                    }
                    break;
                }
            }
            pEntry = pEntry->next;
        }
    }
    else{
        cout<< "There is no such event." << endl;
    }
}
//method to process cmd - "find" "range"
void find_range_event(struct hash_table_entry **t,int event_id, int hash_size, int num_file,
                      const int year_index[], struct annual_storms * annual_storms_save){
    int key;
    key = hash_fun(hash_size,event_id);
    hash_table_entry * en = t[key];
    if (en!= NULL){
        while(en!= NULL){
            
            if (en->event_id == event_id){
                
                
                int yyyy = en->year;
                int index=0;
                for (int i=0;i<num_file;i++){
                    if (yyyy == year_index[i])
                        index = i;
                }
                cout<< "State: "<< annual_storms_save[index].events[en->event_index].state << endl;
                cout<< "Event ID: "<< en->event_id<< endl;
                cout<< "Year: "<< annual_storms_save[index].events[en->event_index].year<< endl;
                cout<< "Event Type: "<< annual_storms_save[index].events[en->event_index].event_type<< endl;
                cout<< "County/Zone Type: "<< annual_storms_save[index].events[en->event_index].cz_type<< endl;
                cout<< "County/Zone Name: "<< annual_storms_save[index].events[en->event_index].cz_name<< endl;
                cout << endl;



                break;
            }
            en = en->next;
        }
    }
    else{
        cout<< "No event found." << endl;
    }
}
/*
void maxAllDamageProperty(storm_event * all_event_save, int n, int file_size){
    for (int i=0; i<n; i++){
        build_max_heap_property(all_event_save, file_size);
        build_max_heap_property(all_event_save, file_size);
        build_max_heap_property(all_event_save, file_size);
        cout << "Event ID: "<< all_event_save[0].event_id <<"; Event Type: "
             <<all_event_save[0].event_type <<"; Damage Amount: $"<< all_event_save[0].damage_property<<endl << endl;
        all_event_save = delete_max_heap_property(all_event_save,file_size);
        file_size = file_size-1;
    }
    file_size=file_size+1;
    int height  = floor(log2(file_size));
    int l_height;
    int r_height;
    int num_leaf = file_size- (int(pow(2.0, double(height)))-1);
    int temp = int(pow(2.0, double(height-1)));
    if (num_leaf>temp){
        l_height = height-1;
        r_height = height-1;
    }
    else{
        l_height = height-1;
        r_height = height-2;
    }

}*/

void maxAllDamageProperty(storm_event * all_event_save, int n, int file_size){
    for (int i=0; i<n; i++){
        maxHeapCropsBuild(all_event_save, file_size);
        maxHeapCropsBuild(all_event_save, file_size);
        maxHeapCropsBuild(all_event_save, file_size);

        cout << "Event ID: "<< all_event_save[0].event_id <<"; Event Type: "
             <<all_event_save[0].event_type <<"; Damage Amount: $"<< all_event_save[0].damage_crops<<endl << endl;
        all_event_save = delete_max_heap_crops(all_event_save,file_size);
        file_size = file_size-1;
    }
    file_size=file_size+1;
    int height  = floor(log2(file_size));
    int l_height;
    int r_height;
    int num_leaf = file_size- (int(pow(2.0, double(height)))-1);
    int temp = int(pow(2.0, double(height-1)));
    if (num_leaf>temp){
        l_height = height-1;
        r_height = height-1;
    }
    else{
        l_height = height-1;
        r_height = height-2;
    }

}

void find_max_fatality(max_fatality * all_fatality_save, int n, struct hash_table_entry **t,
                       int file_size, int hash_size, int num_file,
                       const int year_index[], struct annual_storms * annual_storms_save){
    for (int i=0; i<n; i++){
        cout << "LOOPING : " << i << endl;
        build_max_heap_fatality(all_fatality_save,file_size);
        build_max_heap_fatality(all_fatality_save,file_size);
        findFatality(t,all_fatality_save[0].event_id,hash_size,num_file,year_index,annual_storms_save);
        all_fatality_save = delete_max_heap_fatality(all_fatality_save,file_size);
        file_size = file_size-1;
    }

    int height  = floor(log2(file_size));
    int l_height;
    int r_height;
    int num_leaf = file_size- (int(pow(2.0, double(height)))-1);
    int temp = int(pow(2.0, double(height-1)));
    if (num_leaf>temp){
        l_height = height-1;
        r_height = height-1;
    }
    else{
        l_height = height-1;
        r_height = height-2;
    }
    cout <<endl;

}

void traversal(struct bst* bst_node){
    if (bst_node !=NULL){
        traversal(bst_node->left);
        cout << bst_node->event_id<< " "<< bst_node->s << endl;
        traversal(bst_node->right);
    }
}

struct bst* new_bst(int event_id, char* s){
    
    struct bst*temp = new bst;
    temp->s = s;
    temp->event_id = event_id;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct bst* insert(struct bst* bst_node, int event_id, char*s){
    if (bst_node==NULL){
        bst_node = new_bst(event_id,s);
        return bst_node;
    }
    int result;
    result = cMonth(s, bst_node->s);
    if (result==0){
        bst_node->left = insert(bst_node->left,event_id,s);
    }
    else if (result==1){
        bst_node->right = insert(bst_node->right,event_id,s);
    }
    return bst_node;
}

void inOrderTraversal(struct bst* bst_node, char* low, char* high,
                             struct hash_table_entry **t,int event_id, int hash_size, int num_file,
                             const int year_index[], struct annual_storms * annual_storms_save){
    if (bst_node !=NULL){
        inOrderTraversal(bst_node->left, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        int n1 = cMonth(low,bst_node->s);
        int n2 = cMonth(bst_node->s,high);
        if ( n1==0 && n2==0){
            boolFlag = true;
            find_range_event(t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        }
        inOrderTraversal(bst_node->right, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
    }
}





int find_height(struct bst* bst_node){
    if (bst_node == NULL){
        return -1;
    }
    int left_height = find_height(bst_node->left);
    int right_height = find_height(bst_node->right);
    if (left_height>right_height){
        return left_height+1;
    }
    else{
        return right_height+1;
    }
}
/*
void inorder_traversal_state(struct bst* bst_node, char* low, char* high,
                             struct hash_table_entry **t,int event_id, int hash_size, int num_file,
                             const int year_index[], struct annual_storms * annual_storms_save){
    if (bst_node !=NULL){
        inorder_traversal_state(bst_node->left, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        int n1 = compare_state(low,bst_node->s);
        int n2 = compare_state(bst_node->s,high);
        if ( n1==0 && n2==0){
            boolFlag=true;
            cout <<"State: "<< bst_node->s;
            find_range_event(t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        }
        inorder_traversal_state(bst_node->right, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
    }
}*/
int main(int argc, const char* argv[] ) {
    string num(argv[1]);
    //convert number of files to process from cmd line to int
    int numberOfFiles = convertStringToInt(num);
    new annual_storms;
    annual_storms* pAnnualStorms = new annual_storms[numberOfFiles];
    annual_fatality * pAnnualFatality = new annual_fatality[numberOfFiles];
    int f_FSize[numberOfFiles] ;
    int f_DSize[numberOfFiles];
    int yearIndex[numberOfFiles];
    for (int i=0; i<numberOfFiles; i++){
        string year (argv[i+2]);
        string name;
        name = "fatalities-"+year+".csv";
        yearIndex[i]= convertStringToInt(year);
        fstream file_F(name.c_str() );
        string line;
        if(!file_F.is_open()) std::cout << "ERROR: File Open" << '\n';
        int file_size_F = 0;
        while(file_F.good()){
            getline ( file_F, line); // read a string
            if (!line.empty()) {
                file_size_F++;
            }
        }
        file_F.close();
        file_size_F = file_size_F-1;
        f_FSize[i]=file_size_F;


        string name_1;
        name_1 = "details-"+year+".csv";

        fstream file(name_1.c_str() );
        string value;
        if(!file.is_open()) std::cout << "ERROR: File Open" << '\n';
        int file_size = 0;
        while(file.good()){
            getline ( file, value); // read a string
            if (!value.empty()) {
                file_size++;
            }
        }
        file.close();
        file_size = file_size-1;
        f_DSize[i] = file_size;

        fatality_event* fatality_event_save = new fatality_event[file_size_F];
        storm_event * storm_event_save = new storm_event[file_size];
        fstream file_F_1(name.c_str() );
        build_fatalities_structure(file_F_1, fatality_event_save, file_size_F);
        fstream file_1(name_1.c_str() );
        buildEventStruct(file_1,storm_event_save,file_size,fatality_event_save,file_size_F);
        int count =1;
        for (int j=0; j<file_size_F; j++){
            if (j+1<file_size_F){
                if (fatality_event_save[j].event_id != fatality_event_save[j+1].event_id){
                    count++;
                }
            }
        }
        max_fatality * max_fatality_save = new max_fatality[count];
        int m=0;
        int arr[file_size_F];
        for (int gg = 0;gg<file_size_F;gg++){
            arr[gg] = 0;
        }
        for (int j=0;j<file_size_F;j++){
            int temp_count =1;
            if (arr[j]==1){
                continue;
            }
            if (j+1<file_size_F){
                for (int k = j+1; k<file_size_F; k++){
                    if (fatality_event_save[j].event_id == fatality_event_save[k].event_id){
                        arr[k] = 1;
                        temp_count++;
                    }
                }
                max_fatality_save[m].event_id = fatality_event_save[j].event_id;
                max_fatality_save[m].num_fatality = temp_count;
                max_fatality_save[m].year = yearIndex[i];
                m++;
            }
            else{
                max_fatality_save[m].event_id = fatality_event_save[j].event_id;
                max_fatality_save[m].num_fatality = temp_count;
                max_fatality_save[m].year = yearIndex[i];
            }
        }
        pAnnualFatality[i].year = yearIndex[i];
        pAnnualFatality[i].num_all_fatality = count;
        pAnnualFatality[i].fatality = max_fatality_save;

        pAnnualStorms[i].year = convertStringToInt(year);
        pAnnualStorms[i].events = storm_event_save;
    }

    int total_file_size = 0;
    for (int i=0;i<numberOfFiles;i++){
        total_file_size = total_file_size+f_DSize[i];
    }
    int hash_size = nextPrime(2*total_file_size);
    // cout<< hash_size << endl;

    struct hash_table_entry **t;
    t = static_cast<hash_table_entry **>(malloc(sizeof(*t) * hash_size));
//    t = new hash_table_entry*[hash_size]();


    for (int i=0;i<numberOfFiles;i++){
        build_hash_table(t, hash_size, f_DSize[i], pAnnualStorms[i].events);
    }
    int load=0;
    for (int i=0;i<hash_size;i++){
        if (t[i]!=NULL){
            load++;
        }
    }
    float load_factor = float(load)/float(hash_size);
    int n;

    string line;
    string value;
    getline(std::cin, line);
    n = convertStringToInt(line);
    cout << n << endl << endl;

    for(int k=0;k<n;k++) {

        cout <<"Query: ";
        getline(std::cin, line);
        cout << line << endl << endl;
        std::stringstream is(line);
        string value;
        int num_words=0;
        while (is>>value){
            num_words++;
        }
        std::stringstream iss(line);
        string commandVar[num_words];
        int i=0;
        while (iss>>value){
            commandVar[i]= value;
            i++;
        }
        if (num_words == 3){
            int key = convertStringToInt(commandVar[2]);
            find_event(t, key, hash_size, numberOfFiles, yearIndex, pAnnualStorms);
            cout << endl;

        }
        if (commandVar[0] == "range"){



            //
            if (commandVar[1]=="all"){
                int year = 0;
                storm_event * all_event_save = new storm_event[total_file_size];
                for (int i=0; i<numberOfFiles; i++){
                    for (int j=0; j<f_DSize[i];j++){
                        all_event_save[year]=pAnnualStorms[i].events[j];
                        year++;
                    }
                }
                if (commandVar[2]=="state"){
                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    char tempLowMonth[MONTH_LEN];
                    char tempHighMonth[MONTH_LEN];

                    int low_size = sizeof(low) / sizeof(char);
                    int high_size = sizeof(high) / sizeof(char);


                    // DELETE
                    strcpy(low,commandVar[3].c_str());
                    strcpy(high,commandVar[4].c_str());

                    strcpy(tempLowMonth,commandVar[3].c_str());
                    strcpy(tempHighMonth,commandVar[4].c_str());
                    string lowStrFromChar = convertToString(tempLowMonth, low_size);
                    string highStrFromChar = convertToString(tempHighMonth, high_size);
                    lowStrFromChar = removeQuotes(lowStrFromChar);
                    highStrFromChar = removeQuotes(highStrFromChar);
                    strcpy(low,lowStrFromChar.c_str());
                    strcpy(high,highStrFromChar.c_str());

                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, all_event_save[0].event_id,all_event_save[0].state);
                    for (int i=1;i<total_file_size;i++){
                        insert(bst_node, all_event_save[i].event_id,all_event_save[i].state);
                    }
                    inOrderTraversal(bst_node, low, high,t,bst_node->event_id, hash_size,
                                            numberOfFiles,yearIndex,pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for the given range"<< endl << endl;
                    }


                }else if (commandVar[2]=="month_name"){

                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    char tempLowMonth[MONTH_LEN];
                    char tempHighMonth[MONTH_LEN];

                    int low_size = sizeof(low) / sizeof(char);
                    int high_size = sizeof(high) / sizeof(char);


                    // DELETE
                    strcpy(low,commandVar[3].c_str());
                    strcpy(high,commandVar[4].c_str());

                    strcpy(tempLowMonth,commandVar[3].c_str());
                    strcpy(tempHighMonth,commandVar[4].c_str());
                    string lowStrFromChar = convertToString(tempLowMonth, low_size);
                    string highStrFromChar = convertToString(tempHighMonth, high_size);
                    lowStrFromChar = removeQuotes(lowStrFromChar);
                    highStrFromChar = removeQuotes(highStrFromChar);
                    strcpy(low,lowStrFromChar.c_str());
                    strcpy(high,highStrFromChar.c_str());
                    cout << " low : " << low << endl;
                    cout << " high : " << high<< endl;



                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, all_event_save[0].event_id,all_event_save[0].month_name);
                    for (int i=1;i<total_file_size;i++){
                        insert(bst_node, all_event_save[i].event_id,all_event_save[i].month_name);
                    }
                    inOrderTraversal(bst_node, low, high,t,bst_node->event_id, hash_size,
                                            numberOfFiles,yearIndex,pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for the given range"<< endl<< endl;
                    }

                }
            }
            else{
                // for a sepcific year
                int year = convertStringToInt(commandVar[1]);
                int index=0;
                for (int i=0;i<numberOfFiles;i++){
                    if (year == yearIndex[i])
                        index = i;
                }
                if (commandVar[2]=="state"){
                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    char tempLowMonth[MONTH_LEN];
                    char tempHighMonth[MONTH_LEN];

                    int low_size = sizeof(low) / sizeof(char);
                    int high_size = sizeof(high) / sizeof(char);


                    // DELETE


                    strcpy(tempLowMonth,commandVar[3].c_str());
                    strcpy(tempHighMonth,commandVar[4].c_str());
                    string lowStrFromChar = removeQuotes(convertToString(tempLowMonth, low_size));;
                    string highStrFromChar = removeQuotes(convertToString(tempHighMonth, high_size));
                    strcpy(low,lowStrFromChar.c_str());
                    strcpy(high,highStrFromChar.c_str());

                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, pAnnualStorms[index].events[0].event_id,
                                      pAnnualStorms[index].events[0].state);
                    for (int i=1;i<f_DSize[index];i++){
                        insert(bst_node, pAnnualStorms[index].events[i].event_id,
                               pAnnualStorms[index].events[i].state);
                    }
                    inOrderTraversal(bst_node, low, high,t,bst_node->event_id, hash_size,
                                            numberOfFiles,yearIndex,pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for the given range"<< endl << endl;
                    }

                }
                else if (commandVar[2]=="month_name"){
                //Executes if command is in form
                // YYYY - year (int)
                //range YYYY month_name "January" "January"

                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    char tempLowMonth[MONTH_LEN];
                    char tempHighMonth[MONTH_LEN];

                    int low_size = sizeof(tempLowMonth) / sizeof(char);
                    int high_size = sizeof(tempHighMonth) / sizeof(char);





                    //strcpy(tempLowMonth,low);
                    //strcpy(tempHighMonth,high);
                    strcpy(tempLowMonth,commandVar[3].c_str());
                    strcpy(tempHighMonth,commandVar[4].c_str());

                    string lowStrFromChar = removeQuotes(convertToString(tempLowMonth, low_size));
                    string highStrFromChar = removeQuotes(convertToString(tempHighMonth, high_size));
                    /*lowStrFromChar = removeQuotes(lowStrFromChar);
                    highStrFromChar = removeQuotes(highStrFromChar);*/
                    strcpy(low,lowStrFromChar.c_str());
                    strcpy(high,highStrFromChar.c_str());
                    printf("LOW ::::%s\n",low);

                    printf("High ::::%s\n",high);



                    /*int pos = 0;
                    while ((pos = lowStrFromChar.find('"', pos)) != std::string::npos){
                    lowStrFromChar = lowStrFromChar.erase(pos, 1);
                    }//
                    cout <<"L: "<< lowStrFromChar << endl;

                    pos = 0;
                    while ((pos = highStrFromChar.find('"', pos)) != std::string::npos){
                    highStrFromChar = lowStrFromChar.erase(pos, 1);

                    }*/












                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, pAnnualStorms[index].events[0].event_id,
                                      pAnnualStorms[index].events[0].month_name);
                    for (int i=1;i<f_DSize[index];i++){
                        insert(bst_node, pAnnualStorms[index].events[i].event_id,
                               pAnnualStorms[index].events[i].month_name);
                    }
                    inOrderTraversal(bst_node, low, high,t,bst_node->event_id, hash_size,
                                            numberOfFiles,yearIndex,pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for the given range"<< endl<< endl;
                    }

                }
            }



            //this else statement executes therefore command[0] is "find"
        } else{




            /*
            if (commandVar[1] == "all"){
                // for all years
                int year = 0;
                storm_event * all_event_save = new storm_event[total_file_size];
                for (int i=0; i<numberOfFiles; i++){
                    for (int j=0; j<f_DSize[i];j++){
                        all_event_save[year]=pAnnualStorms[i].events[j];
                        year++;
                    }
                }
                if (commandVar[2] == "state"){
                    char lState[STATE_LEN];
                    char hState[STATE_LEN];
                    strcpy(lState, commandVar[4].c_str());
                    strcpy(hState, commandVar[3].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, all_event_save[0].event_id,all_event_save[0].state);
                    for (int i=1;i<total_file_size;i++){
                        insert(bst_node, all_event_save[i].event_id,all_event_save[i].state);
                    }
                    inorder_traversal_state(bst_node, lState, hState, t, bst_node->event_id, hash_size,
                                            numberOfFiles, yearIndex, pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;

                }
                else if (commandVar[2] == "month_name"){
                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    strcpy(low, commandVar[4].c_str());
                    strcpy(high, commandVar[3].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, all_event_save[0].event_id,all_event_save[0].month_name);
                    for (int i=1;i<total_file_size;i++){
                        insert(bst_node, all_event_save[i].event_id,all_event_save[i].month_name);
                    }
                    inOrderTraversal(bst_node, low, high, t, bst_node->event_id, hash_size,
                                     numberOfFiles, yearIndex, pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;
                }
            }
            else{
                // for a sepcific year
                int year = convertStringToInt(commandVar[1]);
                int index=0;
                for (int i=0;i<numberOfFiles;i++){
                    if (year == yearIndex[i])
                        index = i;
                }
                if (commandVar[2] == "state"){
                    char low[STATE_LEN];
                    char high[STATE_LEN];
                    strcpy(low, commandVar[4].c_str());
                    strcpy(high, commandVar[3].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, pAnnualStorms[index].events[0].event_id,
                                      pAnnualStorms[index].events[0].state);
                    for (int i=1;i<f_DSize[index];i++){
                        insert(bst_node, pAnnualStorms[index].events[i].event_id,
                               pAnnualStorms[index].events[i].state);
                    }
                    inorder_traversal_state(bst_node, low, high, t, bst_node->event_id, hash_size,
                                            numberOfFiles, yearIndex, pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;
                }
                else if (commandVar[2] == "month_name"){
                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    strcpy(low, commandVar[4].c_str());
                    strcpy(high, commandVar[3].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, pAnnualStorms[index].events[0].event_id,
                                      pAnnualStorms[index].events[0].month_name);
                    for (int i=1;i<f_DSize[index];i++){
                        insert(bst_node, pAnnualStorms[index].events[i].event_id,
                               pAnnualStorms[index].events[i].month_name);
                    }
                    inOrderTraversal(bst_node, low, high, t, bst_node->event_id, hash_size,
                                     numberOfFiles, yearIndex, pAnnualStorms);
                    if (!boolFlag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;
                }
            }
        }
        else{*/
            if (commandVar[1] == "max"){
                if (commandVar[2] == "fatality"){
                    int num = convertStringToInt(commandVar[4]);
                    // do find fatality
                    if (commandVar[3] == "all"){
                        // find all years
                        int fatality_size = 0;
                        for (int i=0; i<numberOfFiles; i++){
                            fatality_size = fatality_size + pAnnualFatality[i].num_all_fatality;
                        }
                        max_fatality * all_fatality_save = new max_fatality[fatality_size];
                        int year=0;
                        for (int i=0; i<numberOfFiles; i++){
                            for (int j=0; j < pAnnualFatality[i].num_all_fatality; j++){
                                all_fatality_save[year]=pAnnualFatality[i].fatality[j];
                                year++;
                            }
                        }
                        find_max_fatality(all_fatality_save, num, t, fatality_size,hash_size, numberOfFiles, yearIndex, pAnnualStorms);
                        cout << endl;
                    }
                    else{
                        // a specific year
                        int year = convertStringToInt(commandVar[3]);
                        int index=0;
                        cout << " FIND MAX FATALITY --";
                        cout << " YEAR: " << year <<  endl;
                        for (int i=0;i<numberOfFiles;i++){
                            if (year == yearIndex[i])
                                index = i;
                        }
                        // REV DELETE
                        find_max_fatality(pAnnualFatality[index].fatality, num,t, pAnnualFatality[index].num_all_fatality, hash_size, numberOfFiles, yearIndex, pAnnualStorms);
                        cout << endl;
                    }
                }// STAY HERE
                else{
                    // B - commandVar[2]
                    int num = convertStringToInt(commandVar[4]);
                    // B -if (commandVar[4] == "all"){
                    if (commandVar[2] == "all"){
                        int year = 0;
                        // find from all years
                        // for all years, use this
                        storm_event * all_event_save = new storm_event[total_file_size];
                        for (int i=0; i<numberOfFiles; i++){
                            for (int j=0; j<f_DSize[i];j++){
                                all_event_save[year]=pAnnualStorms[i].events[j];
                                year++;
                            }
                        }
                        if (commandVar[3] == "damage_property"){
                            maxAllDamageProperty(all_event_save, num, total_file_size);
                            cout << endl;
                        }
                        else{
                            maxAllDamageProperty(all_event_save, num, total_file_size);
                            cout << endl;
                        }
                    }
                    else{
                        // B - int year = convertStringToInt(commandVar[4]);
                        //int year = convertStringToInt(commandVar[2]);
                        int year = convertStringToInt(commandVar[2]);
                        // find from a specific year
                        int index=0;
                        for (int i=0;i<numberOfFiles;i++){
                            if (year == yearIndex[i])
                                index = i;
                        }
                        if (commandVar[3] == "damage_property"){
                            maxAllDamageProperty(pAnnualStorms[index].events, num, f_DSize[index]);
                            // REV
                            cout << endl;
                        }
                        else{
                            maxAllDamageProperty(pAnnualStorms[index].events, num, f_DSize[index]);
                            cout << endl;
                        }
                    }
                }
            }
        }
    }

    free(t);
    return 0;
}

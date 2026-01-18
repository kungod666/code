#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// ====================== 定义核心结构体（数据存储） ======================
// 1. 会员信息
struct Member {
    char id[20];     // 会员编号
    char name[20];   // 姓名
    int isBuyHouse;  // 是否购房：0=未购房 1=已购房
};

// 2. 房屋信息
struct House {
    char houseId[20];// 房屋编号
    char address[50];// 地址
    int isSelected;  // 是否被选中：0=未选 1=已选
    int isSold;      // 是否售出：0=未售 1=已售
};

// 3. 入住信息
struct CheckIn {
    char memberId[20];// 入住会员编号
    char houseId[20]; // 入住房屋编号
    int isCheckIn;    // 是否入住：0=未入住 1=已入住
};

// 4. 娱乐设施信息
struct Facility {
    char facId[20];   // 设施编号
    char name[30];    // 设施名称（如泳池、健身房）
    int isUsed;       // 是否被使用：0=未使用 1=使用中
};

// 5. 服务人员信息
struct Staff {
    char staffId[20]; // 员工编号
    char name[20];    // 姓名
    char serveObj[20];// 服务对象（会员编号）
};

// 6. 班车信息（链表节点）
struct BusNode {
    char busId[20];   // 班车编号
    char route[50];   // 班车路线
    int seatCount;    // 座位总数
    int usedSeat;     // 已用座位数
    struct BusNode *next;//链表指针
};

// 7. 班车乘车记录
struct BusRecord {
    char memberId[20];// 乘车会员编号
    char busId[20];   // 乘坐班车编号
    char rideTime[20];// 乘车时间（格式：YYYY-MM-DD HH:MM）
};

// ====================== 全局变量 ======================
struct Member members[50];     // 会员数组
struct House houses[30];       // 房屋数组
struct CheckIn checkIns[50];   // 入住数组
struct Facility facilities[20];// 设施数组
struct Staff staffs[20];       // 服务人员数组
struct BusNode *busHead = NULL;// 班车链表头节点
struct BusRecord busRecords[50];// 乘车记录数组

int memCount = 0;  // 会员数量
int houseCount = 0;// 房屋数量
int checkCount = 0;// 入住记录数量
int facCount = 0;  // 设施数量
int staffCount = 0;// 服务人员数量
int recordCount = 0;// 乘车记录数量

// ====================== 班车链表辅助函数 ======================
// 释放班车链表内存
void freeBusList() {
    struct BusNode *temp, *nextNode;
    temp = busHead;
    while (temp != NULL) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    busHead = NULL;
}

// 获取班车数量
int getBusCount() {
    int count = 0;
    struct BusNode *temp = busHead;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// 根据班车编号查找节点
struct BusNode* findBusById(char *busId) {
    struct BusNode *temp = busHead;
    while (temp != NULL) {
        if (strcmp(temp->busId, busId) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// ====================== 文件持久化核心函数 ======================
// 1. 会员数据读写
void saveMembersToFile(){
    FILE *fp=fopen("members.txt", "w");
    if (!fp){
        printf("会员文件打开失败！\n");
        return;
    }
    for (int i=0; i<memCount;i++){
        fprintf(fp,"%s %s %d\n",members[i].id,members[i].name,members[i].isBuyHouse);
    }
    fclose(fp);
}

void loadMembersFromFile(){
    FILE *fp=fopen("members.txt","r");
    if (!fp){
        printf("会员文件不存在，将新建！\n");
        return;
    }
    struct Member m;
    while(fscanf(fp,"%s %s %d",m.id,m.name,&m.isBuyHouse)!= EOF){
        members[memCount]=m;
        memCount++;
    }
    fclose(fp);
}

// 2. 房屋数据读写
void saveHousesToFile(){
    FILE *fp=fopen("houses.txt","w");
    if (!fp){
        printf("房屋文件打开失败！\n");
        return;
    }
    for(int i=0; i<houseCount;i++){
        fprintf(fp,"%s %s %d %d\n",houses[i].houseId,houses[i].address,houses[i].isSelected,houses[i].isSold);
    }
    fclose(fp);
}

void loadHousesFromFile(){
    FILE *fp=fopen("houses.txt","r");
    if (!fp){
        printf("房屋文件不存在，将新建！\n");
        return;
    }
    struct House h;
    while (fscanf(fp,"%s %s %d %d",h.houseId,h.address,&h.isSelected,&h.isSold)!=EOF){
        houses[houseCount]=h;
        houseCount++;
    }
    fclose(fp);
}

// 3. 入住数据读写
void saveCheckInsToFile(){
    FILE *fp=fopen("checkIns.txt","w");
    if (!fp){
        printf("入住文件打开失败！\n");
        return;
    }
    for(int i=0;i<checkCount;i++){
        fprintf(fp,"%s %s %d\n",checkIns[i].memberId,checkIns[i].houseId,checkIns[i].isCheckIn);
    }
    fclose(fp);
}

void loadCheckInsFromFile(){
    FILE *fp=fopen("checkIns.txt","r");
    if (!fp){
        printf("入住文件不存在，将新建！\n");
        return;
    }
    struct CheckIn c;
    while(fscanf(fp,"%s %s %d",c.memberId,c.houseId,&c.isCheckIn)!=EOF){
        checkIns[checkCount]=c;
        checkCount++;
    }
    fclose(fp);
}

// 4. 设施数据读写
void saveFacilitiesToFile(){
    FILE *fp=fopen("facilities.txt","w");
    if (!fp){
        printf("设施文件打开失败！\n");
        return;
    }
    for (int i=0;i<facCount;i++){
        fprintf(fp,"%s %s %d\n",facilities[i].facId,facilities[i].name,facilities[i].isUsed);
    }
    fclose(fp);
}

void loadFacilitiesFromFile(){
    FILE *fp=fopen("facilities.txt","r");
    if (!fp){
        printf("设施文件不存在，将新建！\n");
        return;
    }
    struct Facility f;
    while (fscanf(fp,"%s %s %d",f.facId,f.name,&f.isUsed)!=EOF){
        facilities[facCount]=f;
        facCount++;
    }
    fclose(fp);
}

// 5. 服务人员数据读写
void saveStaffsToFile(){
    FILE *fp=fopen("staffs.txt","w");
    if (!fp){
        printf("服务人员文件打开失败！\n");
        return;
    }
    for(int i=0;i<staffCount;i++){
        fprintf(fp,"%s %s %s\n",staffs[i].staffId,staffs[i].name,staffs[i].serveObj);
    }
    fclose(fp);
}

void loadStaffsFromFile(){
    FILE *fp=fopen("staffs.txt","r");
    if (!fp){
        printf("服务人员文件不存在，将新建！\n");
        return;
    }
    struct Staff s;
    while (fscanf(fp,"%s %s %s",s.staffId,s.name,s.serveObj)!=EOF){
        staffs[staffCount]=s;
        staffCount++;
    }
    fclose(fp);
}

// 6. 班车数据读写（链表版）
void saveBusesToFile(){
    FILE *fp=fopen("buses.txt","w");
    if (!fp){
        printf("班车文件打开失败！\n");
        return;
    }
    struct BusNode *temp=busHead;
    while (temp!=NULL){
        fprintf(fp,"%s %s %d %d\n",temp->busId,temp->route,temp->seatCount,temp->usedSeat);
        temp=temp->next;
    }
    fclose(fp);
}

void loadBusesFromFile(){
    // 先清空原有链表
    freeBusList();

    FILE *fp=fopen("buses.txt","r");
    if (!fp){
        printf("班车文件不存在，将新建！\n");
        return;
    }
    char busId[20],route[50];
    int seatCount,usedSeat;
    while(fscanf(fp,"%s %s %d %d",busId, route,&seatCount,&usedSeat)!=EOF){
        struct BusNode *newNode=(struct BusNode *)malloc(sizeof(struct BusNode));
        strcpy(newNode->busId,busId);
        strcpy(newNode->route,route);
        newNode->seatCount=seatCount;
        newNode->usedSeat=usedSeat;
        newNode->next=NULL;
        // 尾插法插入链表
        if (busHead==NULL) {
            busHead=newNode;
        }else{
            struct BusNode *p=busHead;
            while(p->next!=NULL) {
                p=p->next;
            }
            p->next=newNode;
        }
    }
    fclose(fp);
}

// 7. 乘车记录数据读写
void saveBusRecordsToFile(){
    FILE *fp=fopen("busRecords.txt","w");
    if (!fp){
        printf("乘车记录文件打开失败！\n");
        return;
    }
    for (int i=0;i<recordCount;i++){
        fprintf(fp,"%s %s %s\n",busRecords[i].memberId,busRecords[i].busId, busRecords[i].rideTime);
    }
    fclose(fp);
}

void loadBusRecordsFromFile(){
    FILE *fp=fopen("busRecords.txt","r");
    if (!fp){
        printf("乘车记录文件不存在，将新建！\n");
        return;
    }
    struct BusRecord r;
    while(fscanf(fp,"%s %s %s",r.memberId,r.busId,r.rideTime)!=EOF){
        busRecords[recordCount]=r;
        recordCount++;
    }
    fclose(fp);
}

// 加载所有数据（系统启动时调用）
void loadAllData() {
    loadMembersFromFile();
    loadHousesFromFile();
    loadCheckInsFromFile();
    loadFacilitiesFromFile();
    loadStaffsFromFile();
    loadBusesFromFile();
    loadBusRecordsFromFile();
}

// 保存所有数据（每次操作后/系统退出时调用）
void saveAllData() {
    saveMembersToFile();
    saveHousesToFile();
    saveCheckInsToFile();
    saveFacilitiesToFile();
    saveStaffsToFile();
    saveBusesToFile();
    saveBusRecordsToFile();
}

// ====================== 原有功能模块 ======================
// 1. 会员管理模块
void addMember(){
    if (memCount>=50){
        printf("会员数量已达上限！\n");
        return;
    }
    struct Member m;
    printf("请输入会员编号：");
    scanf("%s",m.id);
    printf("请输入会员姓名：");
    scanf("%s",m.name);
    m.isBuyHouse=0; // 初始未购房
    members[memCount]=m;
    memCount++;
    saveMembersToFile(); // 保存至文件
    printf("新建会员成功！\n");
}

// 2. 房屋管理模块
void addHouse(){
    if(houseCount>=30){
        printf("房屋数量已达上限！\n");
        return;
    }
    struct House h;
    printf("请输入房屋编号：");
    scanf("%s",h.houseId);
    printf("请输入房屋地址：");
    scanf("%s",h.address);
    h.isSelected=0; // 初始未被选
    h.isSold=0; // 初始未售出
    houses[houseCount]=h;
    houseCount++;
    saveHousesToFile();
    printf("新建房屋成功！\n");
}

int selectHouse(char *selectId){
    printf("可选房屋列表：\n");
    for(int i=0;i<houseCount;i++){
        if(houses[i].isSelected==0&&houses[i].isSold==0){
            printf("房屋编号：%s，地址：%s\n", houses[i].houseId, houses[i].address);
        }
    }
    printf("请输入要选择的房屋编号：");
    scanf("%s",selectId);
    // 标记房屋为已选
    for(int i=0;i<houseCount;i++){
        if (strcmp(houses[i].houseId,selectId)==0){
            houses[i].isSelected=1;
            saveHousesToFile();
            return 1; // 选择成功
        }
    }
    printf("房屋编号不存在！\n");
    return 0; // 选择失败
}

void buyHouse(){
    char memId[20],houseId[20];
    printf("请输入购房会员编号：");
    scanf("%s",memId);
    // 1. 检查会员是否存在
    int memIndex=-1;
    for(int i=0; i<memCount;i++){
        if(strcmp(members[i].id,memId)==0){
            memIndex=i;
            break;
        }
    }
    if(memIndex==-1){
        printf("会员不存在！\n");
        return;
    }
    // 2. 选择房屋
    if (selectHouse(houseId)==0) return;
    // 3. 标记房屋售出、会员已购房
    for (int i=0; i<houseCount;i++){
        if (strcmp(houses[i].houseId,houseId)==0){
            houses[i].isSold=1;
            members[memIndex].isBuyHouse=1;
            saveHousesToFile();
            saveMembersToFile();
            printf("购买房屋成功！\n");
            return;
        }
    }
}

// 3. 入住管理模块
int selectCheckInPerson(char *memId){
    printf("已购房会员列表：\n");
    for(int i =0; i<memCount;i++){
        if(members[i].isBuyHouse==1){
            printf("会员编号：%s，姓名：%s\n",members[i].id,members[i].name);
        }
    }
    printf("请输入要入住的会员编号：");
    scanf("%s",memId);
    // 检查是否已购房
    for(int i=0; i<memCount;i++){
        if(strcmp(members[i].id,memId)==0&&members[i].isBuyHouse==1){
            return 1; // 入住人合法
        }
    }
    printf("该会员未购房，无法入住！\n");
    return 0;
}

void selectCheckIn(){
    char memId[20], houseId[20];
    // 1. 选择入住人
    if (selectCheckInPerson(memId)==0) return;
    // 2. 选择已购房屋
    printf("请输入该会员购买的房屋编号：");
    scanf("%s", houseId);
    // 3. 记录入住信息
    struct CheckIn c;
    strcpy(c.memberId,memId);
    strcpy(c.houseId,houseId);
    c.isCheckIn = 1; // 标记入住
    checkIns[checkCount] = c;
    checkCount++;
    saveCheckInsToFile();
    printf("入住成功！\n");
}

void applyFacility() {
    char memId[20], facId[20];
    printf("请输入入住会员编号：");
    scanf("%s", memId);
    // 检查是否已入住
    int isCheck = 0;
    for (int i = 0; i < checkCount; i++) {
        if (strcmp(checkIns[i].memberId, memId) == 0 && checkIns[i].isCheckIn == 1) {
            isCheck = 1;
            break;
        }
    }
    if (!isCheck) {
        printf("该会员未入住，无法申请设施！\n");
        return;
    }
    // 选择设施
    printf("可选娱乐设施：\n");
    for (int i = 0; i < facCount; i++) {
        if (facilities[i].isUsed == 0) {
            printf("设施编号：%s，名称：%s\n", facilities[i].facId, facilities[i].name);
        }
    }
    printf("请输入要申请的设施编号：");
    scanf("%s", facId);
    // 标记设施为使用中
    for (int i = 0; i < facCount; i++) {
        if (strcmp(facilities[i].facId, facId) == 0 && facilities[i].isUsed == 0) {
            facilities[i].isUsed = 1;
            saveFacilitiesToFile();
            printf("设施申请成功，服务完成！\n");
            return;
        }
    }
    printf("设施不存在或已被使用！\n");
}

// 4. 场馆设施管理模块
void addFacility() {
    if (facCount >= 20) {
        printf("设施数量已达上限！\n");
        return;
    }
    struct Facility f;
    printf("请输入设施编号：");
    scanf("%s", f.facId);
    printf("请输入设施名称：");
    scanf("%s", f.name);
    f.isUsed = 0; // 初始未使用
    facilities[facCount] = f;
    facCount++;
    saveFacilitiesToFile();
    printf("新建娱乐设施成功！\n");
}

void finishFacility() {
    char facId[20];
    printf("请输入使用完毕的设施编号：");
    scanf("%s", facId);
    for (int i = 0; i < facCount; i++) {
        if (strcmp(facilities[i].facId, facId) == 0 && facilities[i].isUsed == 1) {
            facilities[i].isUsed = 0;
            saveFacilitiesToFile();
            printf("设施已标记为使用完毕！\n");
            return;
        }
    }
    printf("设施不存在或未被使用！\n");
}

// 5. 用户管理模块
void addStaff() {
    if (staffCount >= 20) {
        printf("服务人员数量已达上限！\n");
        return;
    }
    struct Staff s;
    printf("请输入服务人员编号：");
    scanf("%s", s.staffId);
    printf("请输入服务人员姓名：");
    scanf("%s", s.name);
    strcpy(s.serveObj, ""); // 初始无服务对象
    staffs[staffCount] = s;
    staffCount++;
    saveStaffsToFile();
    printf("设置服务人员成功！\n");
}

void selectServeObj() {
    char staffId[20], memId[20];
    printf("请输入服务人员编号：");
    scanf("%s", staffId);
    // 查找服务人员
    int staffIndex = -1;
    for (int i = 0; i < staffCount; i++) {
        if (strcmp(staffs[i].staffId, staffId) == 0) {
            staffIndex = i;
            break;
        }
    }
    if (staffIndex == -1) {
        printf("服务人员不存在！\n");
        return;
    }
    // 选择服务对象（入住会员）
    printf("入住会员列表：\n");
    for (int i = 0; i < checkCount; i++) {
        printf("会员编号：%s\n", checkIns[i].memberId);
    }
    printf("请输入服务对象（会员编号）：");
    scanf("%s", memId);
    strcpy(staffs[staffIndex].serveObj, memId);
    saveStaffsToFile();
    printf("服务对象设置成功！\n");
}

// ====================== 班车管理模块（纯链表实现） ======================
// 1. 新增班车
void addBus() {
    // 限制班车最大数量
    if (getBusCount() >= 10) {
        printf("班车数量已达上限！\n");
        return;
    }
    
    struct BusNode *newNode = (struct BusNode *)malloc(sizeof(struct BusNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    
    printf("请输入班车编号：");
    scanf("%s", newNode->busId);
    // 检查编号是否重复
    if (findBusById(newNode->busId) != NULL) {
        printf("该班车编号已存在！\n");
        free(newNode);
        return;
    }
    
    printf("请输入班车路线（如：小区-地铁站）：");
    scanf("%s", newNode->route);
    printf("请输入班车座位总数：");
    scanf("%d", &newNode->seatCount);
    newNode->usedSeat = 0; // 初始未使用座位
    newNode->next = NULL;
    
    // 尾插法插入链表
    if (busHead == NULL) {
        busHead = newNode;
    } else {
        struct BusNode *temp = busHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    saveBusesToFile(); // 保存班车数据
    printf("新增班车成功！\n");
}

// 2. 会员乘车登记
void registerBusRide() {
    char memId[20], busId[20], rideTime[20];
    printf("请输入入住会员编号：");
    scanf("%s", memId);
    
    // 1. 校验会员是否已入住
    int isCheck = 0;
    for (int i = 0; i < checkCount; i++) {
        if (strcmp(checkIns[i].memberId, memId) == 0 && checkIns[i].isCheckIn == 1) {
            isCheck = 1;
            break;
        }
    }
    if (!isCheck) {
        printf("该会员未入住，无法乘坐班车！\n");
        return;
    }
    
    // 2. 展示可用班车
    printf("可用班车列表：\n");
    struct BusNode *temp = busHead;
    int hasAvailable = 0;
    while (temp != NULL) {
        if (temp->usedSeat < temp->seatCount) {
            hasAvailable = 1;
            printf("班车编号：%s，路线：%s，剩余座位：%d\n",
                   temp->busId, temp->route, temp->seatCount - temp->usedSeat);
        }
        temp = temp->next;
    }
    if (!hasAvailable) {
        printf("暂无可用班车！\n");
        return;
    }
    
    // 3. 选择班车
    printf("请输入要乘坐的班车编号：");
    scanf("%s", busId);
    struct BusNode *targetBus = findBusById(busId);
    if (targetBus == NULL || targetBus->usedSeat >= targetBus->seatCount) {
        printf("班车不存在或座位已满！\n");
        return;
    }
    
    // 4. 录入乘车时间
    printf("请输入乘车时间（格式：YYYY-MM-DD HH:MM）：");
    scanf("%s", rideTime);
    
    // 5. 生成乘车记录
    struct BusRecord r;
    strcpy(r.memberId, memId);
    strcpy(r.busId, busId);
    strcpy(r.rideTime, rideTime);
    busRecords[recordCount] = r;
    recordCount++;
    
    // 6. 更新班车座位数
    targetBus->usedSeat++;
    
    // 7. 保存数据
    saveBusRecordsToFile();
    saveBusesToFile();
    printf("乘车登记成功！\n");
}

// 3. 查看班车乘车记录
void viewBusRecords() {
    if (recordCount == 0) {
        printf("暂无班车乘车记录！\n");
        return;
    }
    printf("===== 班车乘车记录 =====\n");
    for (int i = 0; i < recordCount; i++) {
        printf("记录%d：会员编号=%s，班车编号=%s，乘车时间=%s\n",
               i+1, busRecords[i].memberId, busRecords[i].busId, busRecords[i].rideTime);
    }
    printf("========================\n");
}

// 4. 查看所有班车信息（辅助功能）
void viewAllBuses() {
    if (busHead == NULL) {
        printf("暂无班车信息！\n");
        return;
    }
    printf("===== 所有班车信息 =====\n");
    struct BusNode *temp = busHead;
    int index = 1;
    while (temp != NULL) {
        printf("班车%d：编号=%s，路线=%s，总座位=%d，已用座位=%d，剩余座位=%d\n",
               index++, temp->busId, temp->route, temp->seatCount,
               temp->usedSeat, temp->seatCount - temp->usedSeat);
        temp = temp->next;
    }
    printf("========================\n");
}

// ====================== 主菜单（扩展） ======================
void showMenu() {
    printf("\n===== 房屋入住+场馆设施+班车管理系统 =====\n");
    printf("【会员管理】\n");
    printf("1. 新建会员\n");
    printf("【房屋管理】\n");
    printf("2. 新建房屋\n");
    printf("3. 购买房屋（含选择房屋）\n");
    printf("【入住管理】\n");
    printf("4. 选择入住（入住成功）\n");
    printf("5. 申请娱乐设施\n");
    printf("【场馆设施管理】\n");
    printf("6. 新建娱乐设施\n");
    printf("7. 设施使用完毕\n");
    printf("【用户管理】\n");
    printf("8. 设置服务人员\n");
    printf("9. 选择服务对象\n");
    printf("【班车管理】\n");
    printf("10. 新增班车信息\n");
    printf("11. 会员乘车登记\n");
    printf("12. 查看乘车记录\n");
    printf("13. 查看所有班车信息\n");
    printf("0. 退出系统\n");
    printf("=========================================\n");
}

int main() {
    // 系统启动：加载所有持久化数据
    loadAllData();
    int choice;
    while (1) {
        showMenu();
        printf("请输入操作编号：");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addMember(); break;
            case 2: addHouse(); break;
            case 3: buyHouse(); break;
            case 4: selectCheckIn(); break;
            case 5: applyFacility(); break;
            case 6: addFacility(); break;
            case 7: finishFacility(); break;
            case 8: addStaff(); break;
            case 9: selectServeObj(); break;
            case 10: addBus(); break;          // 新增班车
            case 11: registerBusRide(); break; // 乘车登记
            case 12: viewBusRecords(); break;  // 查看记录
            case 13: viewAllBuses(); break;    // 查看班车信息
            case 0:
                saveAllData(); // 退出前保存所有数据
                freeBusList(); // 释放链表内存
                printf("系统退出成功，所有数据已保存！\n");
                return 0;
            default: printf("输入错误，请重新选择！\n");
        }
    }
}
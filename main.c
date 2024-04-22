#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_COURSES 12
#define STR_LEN 12

#define STU_TITTLE "学生ID\t\t学生姓名\t性别\t专业\t\t班级\t\t总分\t平均学分绩点\n"
#define STU_FORMAT "%-16s%-16s%-8s%-16s%-16s%-8.2lf%.2lf\n"
#define STU_DATA st[i].id, st[i].name, st[i].gender, st[i].major, st[i].className, st[i].totalScore, st[i].avgCreditGPA_major
#define CO_TITTLE "课程ID\t\t课程名\t\t性质\t总学分\n"
#define CO_FORMAT "%-16s%-16s%-8u%.2lf\n"
#define CO_DATA co[i].id, co[i].name, co[i].type, co[i].credit
#define SCORE_TITTLE "学生ID\t\t学生姓名\t课程ID\t\t课程名\t\t总分\t学分\t绩点\t学分绩点\t补考分数\t性质\n"
#define SCORE_FORMAT_1 "%-16s%-16s平均分：%-8.2lf平均学分绩点：%.2lf\n"
#define SCORE_DATA_1 st[i].id, st[i].name, st[i].avgScore, st[i].avgCreditGPA_major
#define SCORE_FORMAT_2 "\t\t\t\t%-16s%-16s%-8.2lf%-8.2lf%-8.2lf%-16.2lf%-16.2lf%d\n"
#define SCORE_DATA_2 st[i]._co[j].id, st[i]._co[j].name, st[i]._co[j].totalScore, st[i]._co[j].credit, st[i]._co[j].gpa, st[i]._co[j].creditGPA, st[i]._co[j].makeupScore, st[i]._co[j].type
#define SORT_SC_TITTLE "学生ID\t\t学生姓名\t总分\t学分\t绩点\t补考\n"
#define SORT_SC_FORMAT "%-16s%-16s%-8.2lf%-8.2lf%-8.2lf%-8.2lf\n"
#define SORT_SC_DATA st[j].id, st[j].name, st[j]._co[i].totalScore, st[j]._co[i].credit, st[j]._co[i].gpa, st[j]._co[i].makeupScore

typedef enum {
    DEGREE_COURSE = 1,
    MAJOR_COMPULSORY_COURSE,
    MAJOR_ELECTIVE_COURSE,
    PUBLIC_COMPULSORY_COURSE,
    PUBLIC_ELECTIVE_COURSE
} tp;

typedef struct {
    char *id;
    char *name;
    double credit;
    double gpa;
    double creditGPA;
    double totalScore;
    double makeupScore;
    tp type;
    char *semester;
    double regularScore;
    double midtermScore;
    double finalScore;
    double experimentScore;
    char *teacher;
} cou;

typedef struct {
    char *id;
    char *name;
    char *major;
    char *className;
    char *gender;
    int _couSize;
    cou _co[MAX_COURSES];
    double avgScore;
    int age;
    double gaokaoScore;
    char *ethnicity;
    char *hometown;
    double totalScore;
    double avgCreditGPA;
    double avgCreditGPA_major;
} stu;

stu st[MAX_STUDENTS];
cou co[MAX_COURSES];
int stuSize = 0;
int couSize = 0;
int main();
// === 1, 2 === //
int menu();
void input_student_info();
void input_course_info();
void input_student_score();
void output_student_info();
void output_course_info();
void output_student_score();
// === 3 === //
int retrive_student_by_ID();
void retrive_student_by_className();
int retrive_course_by_ID();
void update_student_by_ID();
void update_student_by_className();
void update_course_by_ID();
void delete_student_by_ID();
void delete_student_by_className();
void delete_course_by_ID();
// === 4 === //
double get_GPA(double max, double real);
double get_avg_credit_gpa(int i);
double get_avg_credit_gpa_major(int i);
// === 5 === //
double get_total_score(int i);
void swap(stu* lhs, stu* rhs);
void sort_students_by_total_score(int l, int r);
void sort_students_by_student_id(int l, int r);
void sort_students_by_avg_credit_gpa_major(int l, int r);
void sort_students_by_course_score();
void quick_sort_for_per(int l, int r, int i);

void read_from_file();
void write_to_file();
void read_student(char* s);
void read_course(char* s);
void read_score(char* s, int i, int j);

int main() {
    while (1) {
        switch (menu()) {
        case 1:
            input_student_info();
            break;
        case 2:
            input_course_info();
            break;
        case 3:
            input_student_score();
            break;
        case 4:
            output_student_info();
            break;
        case 5:
            output_course_info();
            break;
        case 6:
            output_student_score();
            break;
        case 7:
            retrive_student_by_ID();
            break;
        case 8:
            retrive_student_by_className();
            break;
        case 9:
            retrive_course_by_ID();
            break;
        case 10:
            update_student_by_ID();
            break;
        case 11:
            update_student_by_className();
            break;
        case 12:
            update_course_by_ID();
            break;
        case 13:
            delete_student_by_ID();
            break;
        case 14:
            delete_student_by_className();
            break;
        case 15:
            delete_course_by_ID();
            break;
        case 16:
            sort_students_by_total_score(0, stuSize - 1);
            output_student_info();
            break;
        case 17:
            sort_students_by_student_id(0, stuSize - 1);
            output_student_info();
            break;
        case 18:
            sort_students_by_avg_credit_gpa_major(0, stuSize - 1);
            output_student_info();
            break;
        case 19:
            sort_students_by_course_score();
            break;
        case 20:
            read_from_file();
            break;
        case 21:
            write_to_file();
            break;
        case 0:
            printf("正在退出。。。\n");
            exit(0);
            break;
        default:
            printf("输入非法。。。\n");
        }
        system("pause");
        system("cls");
    }
    return 0;
}

// 菜单函数 === DONE
int menu() {
    printf("===== 学生信息管理系统 =====\n");
    printf("输入：\n");
    printf("    1. 输入学生信息\n");
    printf("    2. 输入课程信息\n");
    printf("    3. 输入学生课程成绩\n");
    printf("输出：\n");
    printf("    4. 输出学生信息\n");
    printf("    5. 输出课程信息\n");
    printf("    6. 输出学生课程成绩\n");
    printf("查找：\n");
    printf("    7. 通过ID查找学生信息\n");
    printf("    8. 通过班级查找学生信息\n");
    printf("    9. 通过ID查找课程信息\n");
    printf("修改：\n");
    printf("    10. 根据ID修改学生信息\n");
    printf("    11. 根据班级修改学生信息\n");
    printf("    12. 根据ID修改课程信息\n");
    printf("删除：\n");
    printf("    13. 根据ID删除学生信息\n");
    printf("    14. 根据班级删除学生信息\n");
    printf("    15. 根据ID删除课程信息\n");
    printf("排序：\n");
    printf("    16. 按总分排序\n");
    printf("    17. 按ID排序\n");
    printf("    18. 按平均学分绩点排序\n");
    printf("    19. 按课程成绩排序\n");
    printf("文件操作：\n");
    printf("    20. 从文件读取数据\n");
    printf("    21. 重写数据到文件\n");
    printf("0. 退出\n");
    printf("请选择：");
    int selection = 0;
    while (scanf("%d", &selection) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
        printf("请选择：");
    }
    return selection;
}

// 输入学生信息函数 === DONE
void input_student_info() {
    int newStu = 0;
    do {
        printf("录入几个学生？（%d/%d）：", stuSize, MAX_STUDENTS);
        while (scanf("%d", &newStu) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("录入几个学生？（%d/%d）：", stuSize, MAX_STUDENTS);
        }
        if (newStu < 0 || newStu + stuSize > MAX_STUDENTS)
            printf("输入非法。。。\n");
    } while (newStu < 0 || newStu + stuSize > MAX_STUDENTS);
    for (int i = stuSize; i < stuSize + newStu; ++i) {
        printf("// === %d === //\n", i + 1);
        printf("ID：");
        char* id = (char*)malloc(sizeof(char) * STR_LEN);
        while (scanf("%s", id) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("ID：");
        }
        st[i].id = id;
        printf("姓名：");
        char* name = (char*)malloc(sizeof(char) * STR_LEN);
        while (scanf("%s", name) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("姓名：");
        }
        st[i].name = name;
        printf("专业：");
        char* major = (char*)malloc(sizeof(char) * STR_LEN);
        while (scanf("%s", major) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("专业：");
        }
        st[i].major = major;
        printf("班级：");
        char* className = (char*)malloc(sizeof(char) * STR_LEN);
        while (scanf("%s", className) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("班级：");
        }
        st[i].className = className;
        printf("性别：");
        char* gender = (char*)malloc(sizeof(char) * STR_LEN);
        while (scanf("%s", gender) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("性别：");
        }
        st[i].gender = gender;
    }
    stuSize += newStu;
    printf("操作成功！\n");
    printf("%d个学生成功录入！\n", newStu);
}

// 输入课程信息函数 === DONE
void input_course_info() {
    int newCou = 0;
    printf("录入几门课？(%d/%d)：", couSize, MAX_COURSES);
    do {
        while (scanf("%d", &newCou) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("录入几门课？(%d/%d)：", couSize, MAX_COURSES);
        }
        if (newCou < 0 || newCou + couSize > MAX_COURSES)
            printf("输入非法。。。\n");
    } while (newCou < 0 || newCou + couSize > MAX_COURSES);
    for (int i = couSize; i < couSize + newCou; ++i) {
        printf("// === %d === //\n", i + 1);
        printf("课程ID：");
        char* id = (char*)malloc(sizeof(char) * STR_LEN);
        while (scanf("%s", id) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("课程ID：");
        }
        co[i].id = id;
        printf("课程名：");
        char* name = (char*)malloc(sizeof(char) * STR_LEN);
        while (scanf("%s", name) != 1) {
            scanf("%*[\n]%*c");
            printf("输入非法。。。\n");
            printf("课程名：");
        }
        co[i].name = name;
        printf(" * 1 = 学位课\n");
        printf(" * 2 = 专业必修课\n");
        printf(" * 3 = 专业选修课\n");
        printf(" * 4 = 公共必修课\n");
        printf(" * 5 = 公共选修课\n");
        do {
            printf("课程性质：");
            while (scanf("%u", &co[i].type) != 1) {
                scanf("%*[^\n]%*c");
                printf("输入非法。。。\n");
                printf("课程性质：");
            }
            if (co[i].type < 1 || co[i].type > 5)
                printf("输入非法。。。\n");
        } while (co[i].type < 1 || co[i].type > 5);
        co[i].totalScore = 100;
        co[i].makeupScore = 100;
        do {
            printf("共多少学分？：");
            while (scanf("%lf", &co[i].credit) != 1) {
                printf("输入非法。。。\n");
                printf("共多少学分？：");
            }
            if (co[i].credit < 0)
                printf("输入非法。。。\n");
        } while (co[i].credit < 0);
    }
    couSize += newCou;
    printf("操作成功！\n");
    printf("%d门课程已录入！\n", newCou);
}

// 输入学生成绩函数 === DONE
void input_student_score() {
    if (stuSize == 0) {
        printf("请先添加学生！\n");
        return;
    }
    if (couSize == 0) {
        printf("请先添加课程！\n");
        return;
    }
    for (int i = 0; i < stuSize; ++i) {
        if (st[i]._couSize == couSize)
            continue;
        printf("\n为该学生录入成绩 -> ID：%s  姓名：%s\n", st[i].id, st[i].name);
        int k = 0;
        for (int j = 0; j < couSize; ++j) {
            int flag = 0;
            for (int x = 0; x < st[i]._couSize; ++x)
                if (strcmp(st[i]._co[x].id, co[j].id) == 0)
                    flag = 1;
            if (flag)
                continue;
            printf("当前课程 -> ID：%s  课程名：%s\n", co[j].id, co[j].name);
            st[i]._co[k].id = co[j].id;
            st[i]._co[k].name = co[j].name;
            st[i]._co[k].type = co[j].type;
            printf("请分别输入 总分 学分 补考成绩：\n");
            while (scanf("%lf %lf %lf", &st[i]._co[k].totalScore, &st[i]._co[k].credit, &st[i]._co[k].makeupScore) != 3) {
                scanf("%^[^\n]%*c");
                printf("输入非法。。。");
            }
           /* do {
                printf("成绩：");
                while (scanf("%lf", &st[i]._co[k].totalScore) != 1) {
                    scanf("%*[^\n]%*c");
                    printf("输入非法。。。\n");
                    printf("成绩：");
                }
                if (st[i]._co[k].totalScore > co[j].totalScore)
                    printf("输入非法。。。\n");
            } while (st[i]._co[k].totalScore > co[j].totalScore);
            do {
                printf("学分：");
                while (scanf("%lf", &st[i]._co[k].credit) != 1) {
                    scanf("%*[^\n]%*c");
                    printf("输入非法。。。\n");
                    printf("学分：");
                }
                if (st[i]._co[k].credit > co[j].credit)
                    printf("输入非法。。。\n");
            } while (st[i]._co[k].credit > co[j].credit);
            do {
                printf("补考成绩：");
                while (scanf("%lf", &st[i]._co[k].makeupScore) != 1) {
                    scanf("%*[^\n]%*c");
                    printf("输入非法。。。\n");
                    printf("补考成绩：");
                }
                if (st[i]._co[k].makeupScore > co[j].makeupScore)
                    printf("输入非法。。。\n");
            } while (st[i]._co[k].makeupScore > co[j].makeupScore);*/
            if (co[j].type == 1)
                st[i]._co[k].gpa = get_GPA(co[j].totalScore, st[i]._co[k].totalScore);
            st[i]._co[k].creditGPA = st[i]._co[k].credit * st[i]._co[k].gpa;
            ++k;
        }
        st[i]._couSize = k;
        st[i].avgCreditGPA = get_avg_credit_gpa(i);
        st[i].avgCreditGPA_major = get_avg_credit_gpa_major(i);
        st[i].totalScore = get_total_score(i);
        st[i].avgScore = st[i].totalScore / st[i]._couSize;
    }
    printf("操作成功！\n");
}

// 输出学生信息函数 === DONE
void output_student_info() {
    if (stuSize == 0) {
        printf("没有学生。。。\n");
        return;
    }
    printf(STU_TITTLE);
    for (int i = 0; i < stuSize; ++i) {
        printf(STU_FORMAT, STU_DATA);
    }
}

// 输出课程信息函数 === DONE
void output_course_info() {
    if (couSize == 0) {
        printf("没有课程。。。\n");
        return;
    }
    printf(CO_TITTLE);
    for (int i = 0; i < couSize; ++i)
        printf(CO_FORMAT, CO_DATA);
}

// 输出学生成绩函数 === DONE
void output_student_score() {
    if (stuSize == 0) {
        printf("没有学生。。。\n");
        return;
    }
    printf(" * 1 = 学位课\n");
    printf(" * 2 = 专业必修课\n");
    printf(" * 3 = 专业选修课\n");
    printf(" * 4 = 公共必修课\n");
    printf(" * 5 = 公共选修课\n");
    printf(SCORE_TITTLE);
    for (int i = 0; i < stuSize; ++i) {
        printf(SCORE_FORMAT_1, SCORE_DATA_1);
        for (int j = 0; j < st[i]._couSize; ++j) {
            printf(SCORE_FORMAT_2, SCORE_DATA_2);
        }
    }
}

// 查询学生函数BYID === DONE
int retrive_student_by_ID() {
    char rID[12];
    printf("输入学生ID：");
    while (scanf("%s", rID) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
        printf("输入学生ID：");
    }
    for (int i = 0; i < stuSize; ++i) {
        if (strcmp(st[i].id, rID) == 0) {
            printf(STU_TITTLE);
            printf(STU_FORMAT, STU_DATA);
            return i;
        }
    }
    printf("不存在。。。\n");
    return -1;
}

// 查询学生函数BYclassName === DONE
void retrive_student_by_className() {
    char rClassName[12];
    int flag = 1;
    printf("输入班级：");
    while (scanf("%s", rClassName) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
        printf("输入班级：");
    }
    printf(STU_TITTLE);
    for (int i = 0; i < stuSize; ++i) {
        if (strcmp(st[i].className, rClassName) == 0) {
            flag = 0;
            printf(STU_FORMAT, STU_DATA);
        }
    }
    if (flag)
        printf("不存在。。。\n");
}

// 查询课程函数 === DONE
int retrive_course_by_ID() {
    char rID[12];
    printf("输入课程ID：");
    while (scanf("%s", rID) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
        printf("输入课程ID：");
    }
    for (int i = 0; i < couSize; ++i) {
        if (strcmp(co[i].id, rID) == 0) {
            printf(CO_TITTLE);
            printf(CO_FORMAT, CO_DATA);
            return i;
        }
    }
    printf("不存在。。。\n");
    return -1;
}

// 修改学生信息函数BYID === DONE
void update_student_by_ID() {
    int i = retrive_student_by_ID();
    if (i != -1) {
        printf("查找成功！请修改：\n");
        printf("ID：");
        while (scanf("%s", st[i].id) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("ID：");
        }
        printf("姓名：");
        while (scanf("%s", st[i].name) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("姓名：");
        }
        printf("专业：");
        while (scanf("%s", st[i].major) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("专业：");
        }
        printf("班级：");
        while (scanf("%s", st[i].className) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("班级：");
        }
        printf("性别：");
        while (scanf("%s", st[i].gender) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("性别：");
        }
    }
}

// 修改学生信息函数BYclassName === DONE
void update_student_by_className() {
    char rClassName[12];
    int flag = 1, cnt = 0;
    printf("输入班级：");
    while (scanf("%s", rClassName) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
        printf("输入班级：");
    }
    for (int i = 0; i < stuSize; ++i) {
        if (strcmp(st[i].className, rClassName) == 0) {
            flag = 0;
            printf(STU_TITTLE);
            printf(STU_FORMAT, STU_DATA);
            printf("查找成功！请修改：\n");
            printf("ID：");
            while (scanf("%s", st[i].id) != 1) {
                scanf("%*[^\n]%*c");
                printf("输入非法。。。\n");
                printf("ID：");
            }
            printf("姓名：");
            while (scanf("%s", st[i].name) != 1) {
                scanf("%*[^\n]%*c");
                printf("输入非法。。。\n");
                printf("姓名：");
            }
            printf("专业：");
            while (scanf("%s", st[i].major) != 1) {
                scanf("%*[^\n]%*c");
                printf("输入非法。。。\n");
                printf("专业：");
            }
            printf("班级：");
            while (scanf("%s", st[i].className) != 1) {
                scanf("%*[^\n]%*c");
                printf("输入非法。。。\n");
                printf("班级：");
            }
            printf("性别：");
            while (scanf("%s", st[i].gender) != 1) {
                scanf("%*[^\n]%*c");
                printf("输入非法。。。\n");
                printf("性别：");
            }
            ++cnt;
        }
    }
    if (flag)
        printf("不存在。。。\n");
    else
        printf("成功修改%d个学生信息！", cnt);
}

// 修改课程信息函数 === DONE
void update_course_by_ID() {
    int i = retrive_course_by_ID();
    if (i != -1) {
        printf("查找成功！请修改：\n");
        printf("ID：");
        while (scanf("%s", co[i].id) != 1) {
            scanf("%*[^\n]%*c");
            printf("输入非法。。。\n");
            printf("ID：");
        }
        printf("课程名：");
        while (scanf("%s", co[i].name) != 1) {
            scanf("%*[\n]%*c");
            printf("输入非法。。。\n");
            printf("课程名：");
        }
        printf(" * 1 = 学位课\n");
        printf(" * 2 = 专业必修课\n");
        printf(" * 3 = 专业选修课\n");
        printf(" * 4 = 公共必修课\n");
        printf(" * 5 = 公共选修课\n");
        do {
            printf("课程性质：");
            while (scanf("%u", &co[i].type) != 1) {
                scanf("%*[^\n]%*c");
                printf("输入非法。。。\n");
                printf("课程性质：");
            }
            if (co[i].type < 1 || co[i].type > 5)
                printf("输入非法。。。\n");
        } while (co[i].type < 1 || co[i].type > 5);
        do {
            printf("请输入总学分：");
            while (scanf("%lf", &co[i].credit) != 1) {
                printf("输入非法。。。\n");
                printf("请输入总学分：");
            }
            if (co[i].credit < 0)
                printf("输入非法。。。\n");
        } while (co[i].credit < 0);
        for (int i = 0; i < stuSize; ++i) {
            for (int j = 0; j < st[i]._couSize; ++j) {
                st[i]._co[j].id = co[j].id;
                st[i]._co[j].name = co[j].name;
                st[i]._co[j].type = co[j].type;
            }
        }
    }
}

// 删除学生函数BYID === DONE
void delete_student_by_ID() {
    int i = retrive_student_by_ID();
    printf("确认要继续吗？(Y/N)：");
    char confirm;
    getchar();
    while (scanf("%c", &confirm) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
    }
    if (confirm == 'N' || confirm == 'n')
        return;
    if (i != -1) {
        for (; i < stuSize - 1; ++i)
            st[i] = st[i + 1];
        --stuSize;
    }
}

// 删除学生函数BYclassName === DONE
void delete_student_by_className() {
    char rClassName[12];
    int flag = 1, temp = stuSize;
    printf("请输入班级：");
    while (scanf("%s", rClassName) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
        printf("请输入班级：");
    }
    for (int i = 0; i < stuSize; ++i) {
        if (strcmp(st[i].className, rClassName) == 0) {
            flag = 0;
            printf(STU_FORMAT, STU_DATA);
        }
    }
    if (flag) {
        printf("不存在。。。\n");
        return;
    }
    printf("确认要继续吗？(Y/N)：");
    char confirm;
    getchar();
    while (scanf("%c", &confirm) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
    }
    if (confirm == 'N' || confirm == 'n')
        return;
    for (int i = 0; i < stuSize; ++i) {
        if (strcmp(st[i].className, rClassName) == 0) {
            for (int j = i; j < stuSize - 1; ++j)
                st[j] = st[j + 1];
            --stuSize;
            --i;
        }
    }
    printf("成功删除%d个学生信息！", temp - stuSize);
}

// 删除课程函数 === DONE
void delete_course_by_ID() {
    char rID[12];
    int flag = 1;
    printf("请输入课程ID：");
    while (scanf("%s", rID) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
        printf("请输入课程ID：");
    }
    printf("确认要继续吗？(Y/N)：");
    char confirm;
    getchar();
    while (scanf("%c", &confirm) != 1) {
        scanf("%*[^\n]%*c");
        printf("输入非法。。。\n");
    }
    if (confirm == 'N' || confirm == 'n')
        return;
    for (int i = 0; i < couSize; ++i) {
        if (strcmp(co[i].id, rID) == 0) {
            flag = 0;
            printf(CO_TITTLE);
            printf(CO_FORMAT, CO_DATA);
            for (; i < couSize - 1; ++i)
                co[i] = co[i + 1];
            --couSize;
        }
    }
    if (flag) {
        printf("不存在。。。\n");
        return;
    }
    for (int i = 0; i < stuSize; ++i) {
        for (int j = 0; j < st[i]._couSize; ++j) {
            if (strcmp(st[i]._co[j].id, rID) == 0) {
                for (; j < st[i]._couSize - 1; ++j)
                    st[i]._co[j] = st[i]._co[j + 1];
                --st[i]._couSize;
            }
        }
    }
}

// 计算绩点函数 === DONE
double get_GPA(double max, double real) {
    // 90-100 4 85-89 3.7 82-84 3.3
    // 78-81 3.0 75-77 2.7 72-74 2.3
    // 68-71 2.0 64-67 1.5 60-63 1.0
    // 60以下 0
    double rate = real / max * 100;
    if (rate <= 100 && rate >= 90)
        return 4;
    else if (rate <= 89 && rate >= 85)
        return 3.7;
    else if (rate <= 84 && rate >= 82)
        return 3.3;
    else if (rate <= 81 && rate >= 78)
        return 3;
    else if (rate <= 77 && rate >= 75)
        return 2.7;
    else if (rate <= 74 && rate >= 72)
        return 2.3;
    else if (rate <= 71 && rate >= 68)
        return 2;
    else if (rate <= 67 && rate >= 64)
        return 1.5;
    else if (rate <= 63 && rate >= 60)
        return 1;
    else
        return 0;
}

// 计算平均学分绩点
double get_avg_credit_gpa(int i) {
    double sumAvgCreditGPA = 0, sumCredit = 0;
    for (int j = 0; j < st[i]._couSize; ++j) {
        sumAvgCreditGPA += st[i]._co[j].creditGPA;
        sumCredit += st[i]._co[j].credit;
    }
    if (sumCredit == 0)
        return 0;
    return sumAvgCreditGPA / sumCredit;
}

// 计算学位课平均学分绩点
double get_avg_credit_gpa_major(int i) {
    double sumAvgCreditGPA = 0, sumCredit = 0;
    for (int j = 0; j < st[i]._couSize; ++j) {
        if (st[i]._co[j].type == 1) {
            sumAvgCreditGPA += st[i]._co[j].creditGPA;
            sumCredit += st[i]._co[j].credit;
        }
    }
    if (sumCredit == 0)
        return 0;
    return sumAvgCreditGPA / sumCredit;
}

// 计算学生总分函数 === DONE
double get_total_score(int i) {
    double sum = 0;
    for (int j = 0; j < st[i]._couSize; ++j)
        sum += st[i]._co[j].totalScore;
    return sum;
}

// 交换两学生的位置 === DONE
void swap(stu* lhs, stu* rhs) {
    stu temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

// 按照总分排序学生函数 === DONE
void sort_students_by_total_score(int l, int r) {
    if (l >= r)
        return;
    int m = (l + r) >> 1;
    if ((st[l].totalScore < st[r].totalScore) ^ (st[l].totalScore < st[m].totalScore))
        m = l;
    else if ((st[r].totalScore < st[l].totalScore) ^ (st[r].totalScore < st[m].totalScore))
        m = r;
    swap(&st[l], &st[m]);
    int i = l, j = r;
    while (i < j) {
        while (i < j && st[j].totalScore <= st[l].totalScore)
            --j;
        while (i < j && st[i].totalScore >= st[l].totalScore)
            ++i;
        swap(&st[i], &st[j]);
    }
    swap(&st[l], &st[i]);
    sort_students_by_total_score(l, i - 1);
    sort_students_by_total_score(i + 1, r);
}

// 按照学号排序学生函数 === DONE
void sort_students_by_student_id(int l, int r) {
    if (l >= r)
        return;
    int m = (l + r) >> 1;
    if ((strcmp(st[l].id, st[r].id) < 0) ^ (strcmp(st[l].id, st[m].id) < 0))
        m = l;
    else if ((strcmp(st[r].id, st[l].id) < 0) ^ (strcmp(st[r].id, st[m].id)))
        m = r;
    swap(&st[l], &st[m]);
    int i = l, j = r;
    while (i < j) {
        while (i < j && strcmp(st[j].id, st[l].id) >= 0)
            --j;
        while (i < j && strcmp(st[i].id, st[l].id) <= 0)
            ++i;
        swap(&st[i], &st[j]);
    }
    swap(&st[l], &st[i]);
    sort_students_by_student_id(l, i - 1);
    sort_students_by_student_id(i + 1, r);
}

// 按照平均学分绩点排序学生函数 === DONE
void sort_students_by_avg_credit_gpa_major(int l, int r) {
    if (l >= r)
        return;
    int m = (l + r) >> 1;
    if ((st[l].avgCreditGPA < st[r].avgCreditGPA_major) ^ (st[l].avgCreditGPA_major < st[m].avgCreditGPA_major))
        m = l;
    else if ((st[r].avgCreditGPA_major < st[l].avgCreditGPA_major) ^ (st[r].avgCreditGPA_major < st[m].avgCreditGPA_major))
        m = r;
    swap(&st[l], &st[m]);
    int i = l, j = r;
    while (i < j) {
        while (i < j && st[j].avgCreditGPA_major <= st[l].avgCreditGPA_major)
            --j;
        while (i < j && st[i].avgCreditGPA_major >= st[l].avgCreditGPA_major)
            ++i;
        swap(&st[i], &st[j]);
    }
    swap(&st[l], &st[i]);
    sort_students_by_avg_credit_gpa_major(l, i - 1);
    sort_students_by_avg_credit_gpa_major(i + 1, r);
}

// 按照每门课程分数排序学生函数 === DONE
void sort_students_by_course_score() {
    for (int i = 0; i < couSize; ++i) {
        printf(CO_TITTLE);
        printf(CO_FORMAT, CO_DATA);
        quick_sort_for_per(0, stuSize - 1, i);
        printf(SORT_SC_TITTLE);
        for (int j = 0; j < stuSize; ++j)
            printf(SORT_SC_FORMAT, SORT_SC_DATA);
        printf("\n");
    }
}

// 排序 -> 按照每门课程分数排序学生函数 === DONE
void quick_sort_for_per(int l, int r, int i) {
    if (l >= r)
        return;
    int m = (l + r) >> 1;
    if ((st[i]._co[l].totalScore < st[i]._co[m].totalScore) ^ (st[i]._co[l].totalScore < st[i]._co[r].totalScore))
        m = l;
    else if ((st[i]._co[r].totalScore < st[i]._co[m].totalScore) ^ (st[i]._co[r].totalScore < st[i]._co[l].totalScore))
        m = r;
    swap(&st[l], &st[m]);
    int a = l, b = r;
    while (a < b) {
        while (a < b && st[i]._co[b].totalScore <= st[i]._co[m].totalScore)
            --b;
        while (a < b && st[i]._co[a].totalScore >= st[i]._co[m].totalScore)
            ++a;
        swap(&st[a], &st[b]);
    }
    swap(&st[l], &st[a]);
    quick_sort_for_per(l, a - 1, i);
    quick_sort_for_per(a + 1, r, i);
}

// 从文件读取信息函数
void read_from_file() {
    int tempS = stuSize, tempC = couSize;
    char s[255];
    FILE* studentFile = fopen("./student.csv", "r+");
    if (studentFile == NULL)
        fprintf(stderr, "打开文件./student.csv失败。。。\n");
    else {
        fgets(s, 255, studentFile);
        while (fgets(s, 255, studentFile) != NULL) {
            if (strdup(s) == '\n')
                break;
            read_student(strdup(s));
            ++stuSize;
        }
        fclose(studentFile);
    }
    FILE* courseFile = fopen("./course.csv", "r+");
    if (courseFile == NULL)
        fprintf(stderr, "打开文件./course.csv失败。。。\n");
    else {
        fgets(s, 255, courseFile);
        while (fgets(s, 255, courseFile) != NULL) {
            if (strdup(s) == '\n')
                break;
            read_course(strdup(s));
            ++couSize;
        }
        fclose(courseFile);
    }
    FILE* scoreFile = fopen("./score.csv", "r+");
    if (scoreFile == NULL)
        fprintf(stderr, "打开文件./score.csv失败。。。\n");
    else {
        int i = tempS, j = 0;
        fgets(s, 255, scoreFile);
        while (fgets(s, 255, scoreFile) != NULL) {
            if (strdup(s) == '\n')
                break;
            read_score(strdup(s), i, j);
            ++j;
            if (j == st[i]._couSize + 1) {
                ++i;
                j = 0;
            }
        }
    }
    fprintf(stdout, "操作成功！\n读取了%d个学生、%d门课程信息。", stuSize - tempS, couSize - tempC);
}

// 将数据写入文件 === DONE
void write_to_file() {
    FILE* studentFile = fopen("./student.csv", "w+");
    if (studentFile == NULL)
        fprintf(stderr, "打开文件./student.csv失败。。。\n");
    else {
        fprintf(studentFile, "学生ID,学生姓名,性别,专业,班级,总分,平均学分绩点(专业课),修读课程数\n");
        for (int i = 0; i < stuSize; ++i) {
            fprintf(studentFile, "%s,%s,%s,%s,%s,%.2lf,%.2lf,", STU_DATA);
            fprintf(studentFile, "%d\n", st[i]._couSize);
        }
        fclose(studentFile);
    }
    FILE* courseFile = fopen("./course.csv", "w+");
    if (courseFile == NULL)
        fprintf(stderr, "打开文件./course.csv失败。。。\n");
    else {
        fprintf(courseFile, "课程ID,课程名,性质,总学分\n");
        for (int i = 0; i < couSize; ++i)
            fprintf(courseFile, "%s,%s,%u,%.2lf\n", CO_DATA);
        fclose(courseFile);
    }
    FILE* scoreFile = fopen("./score.csv", "w+");
    if (scoreFile == NULL)
        fprintf(stderr, "打开文件./score.csv失败。。。\n");
    else {
        fprintf(scoreFile, "学生ID,学生姓名,课程ID,课程名,总分,学分,绩点,学分绩点,补考,性质\n");
        for (int i = 0; i < stuSize; ++i) {
            fprintf(scoreFile, "%s,%s,平均分：,%.2lf,平均学分绩点(专业课)：,%.2lf\n", SCORE_DATA_1);
            for (int j = 0; j < st[i]._couSize; ++j)
                fprintf(scoreFile, ",,%s,%s,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%d\n", SCORE_DATA_2);
        }
        fclose(scoreFile);
    }
    fprintf(stdout, "操作成功！\n%d个学生，%d门课程及成绩都已成功写入文件：\n", stuSize, couSize);
    fprintf(stdout, "./student.csv\n./course.csv\n./score.csv\n");
}

// 从文件录入学生信息 -> read_from_file() === DONE
void read_student(char* s) {
    int i = 0;
    char* token = strtok(s, ",");
    while (token != NULL) {
        switch (i) {
        case 0:
            st[stuSize].id = strdup(token);
            break;
        case 1:
            st[stuSize].name = strdup(token);
            break;
        case 2:
            st[stuSize].gender = strdup(token);
            break;
        case 3:
            st[stuSize].major = strdup(token);
            break;
        case 4:
            st[stuSize].className = strdup(token);
            break;
        case 5:
            st[stuSize].totalScore = atof(token);
            break;
        case 6:
            st[stuSize].avgCreditGPA_major = atof(token);
            break;
        case 7:
            st[stuSize]._couSize = atoi(token);
            return;
        }
        token = strtok(NULL, ",");
        ++i;
    }
}

// 从文件录入课程信息 -> read_from_file() === DONE
void read_course(char* s) {
    int i = 0;
    char* token = strtok(s, ",");
    co[couSize].totalScore = 100;
    co[couSize].makeupScore = 100;
    while (token != NULL) {
        switch (i) {
        case 0:
            co[couSize].id = strdup(token);
            break;
        case 1:
            co[couSize].name = strdup(token);
            break;
        case 2:
            co[couSize].type = atoi(token);
            break;
        case 3:
            co[couSize].credit = atof(token);
            return;
        }
        token = strtok(NULL, ",");
        ++i;
    }
}

// 从文件录入成绩信息 -> read_from_file() === DONE
void read_score(char* s, int i, int j) {
    char* token = strtok(s, ",");
    if (j == 0) {
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        st[i].avgScore = atof(token);
        return;
    }
    int k = 0;
    while (token != NULL) {
        switch (k) {
        case 0:
            st[i]._co[j - 1].id = strdup(token);
            break;
        case 1:
            st[i]._co[j - 1].name = strdup(token);
            break;
        case 2:
            st[i]._co[j - 1].totalScore = atof(token);
            break;
        case 3:
            st[i]._co[j - 1].credit = atof(token);
            break;
        case 4:
            st[i]._co[j - 1].gpa = atof(token);
            break;
        case 5:
            st[i]._co[j - 1].creditGPA = atof(token);
            break;
        case 6:
            st[i]._co[j - 1].makeupScore = atof(token);
            break;
        case 7:
            st[i]._co[j - 1].type = atoi(token);
            return;
        }
        token = strtok(NULL, ",");
        ++k;
    }
}
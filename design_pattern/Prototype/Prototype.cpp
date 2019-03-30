#include <iostream>

class Resume;

class IResume
{
public:
    virtual ~IResume() = default;

    virtual Resume* clone() = 0;
    virtual void show() = 0;
    virtual void setWorkExperience(const std::string company, const std::string period) = 0;
};

class WorkExperience
{
public:

    std::string company_;
    std::string datePeriod_;
};

class Resume: public IResume
{
public:
    Resume(const std::string name,const unsigned age, std::string sex): name_(name), age_(age), sex_(sex), experience_(new WorkExperience()) {}
    Resume(const Resume& resume);
    Resume* clone() override { return new Resume(*this);}

    void setWorkExperience(const std::string company, const std::string period) {experience_->company_ = company; experience_->datePeriod_ = period;}

    void show() override {std::cout << name_ << " " << age_ << " " << sex_ << " " << experience_->company_ << " " << experience_->datePeriod_ << std::endl;}

public:
    std::string name_;
    unsigned age_;
    std::string sex_;
    WorkExperience* experience_;
};

Resume::Resume(const Resume& resume)
{
    this->name_ = resume.name_;
    this->age_ = resume.age_;
    this->sex_ = resume.sex_;
    this->experience_ = new WorkExperience();
    this->experience_->company_ = resume.experience_->company_;
    this->experience_->datePeriod_ = resume.experience_->datePeriod_;
}

int main()
{
    IResume* r1 = new Resume("zhangsan", 255, "male");
    r1->setWorkExperience("gaozhi", "2013-2015");
    r1->show();

    IResume* r2 = r1->clone();
    r2->setWorkExperience("ericsson", "2015-2019");
    r2->show();

    IResume* r3 = r2->clone();
    r3->show();
    delete r1;
    delete r2;
}


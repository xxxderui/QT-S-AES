#include "figure.h"
#include "ui_figure.h"
#include "choice.h"

figure::figure(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::figure)
{
    ui->setupUi(this);
}

figure::~figure()
{
    delete ui;
}

using namespace std;

class SAES {
private:
    // 常量定义
    static const int S_BOX[4][4];
    static const int INVERSE_S_BOX[4][4];
    static const int MIX_COLUMNS_MATRIX[2][2];
    static const int INVERSE_MIX_COLUMNS_MATRIX[2][2];

    // 加密算法的基础函数
    static int addRoundKey(int state, int roundKey) {
        return state ^ roundKey;
    }

    static int substituteBytes(int state, const int sBox[4][4]) {
        // S-Box 替代
        int result = 0;
        result |= (sBox[(state >> 14) & 0x03][(state >> 12) & 0x03] << 12);
        result |= (sBox[(state >> 10) & 0x03][(state >> 8) & 0x03] << 8);
        result |= (sBox[(state >> 6) & 0x03][(state >> 4) & 0x03] << 4);
        result |= (sBox[(state >> 2) & 0x03][state & 0x03]);
        return result;
    }

    static int rowShift(int state) {
        // 行移位
        int first = state & 0xF000;
        int third = state & 0x00F0;
        int second = state & 0x0F00;
        int fourth = state & 0x000F;
        return first | third | ((second >> 8) & 0x000F) | ((fourth << 8) & 0x0F00);
    }

    static int mixColumns(int state, const int matrix[2][2]) {
        // 列混淆
        int columns[4];
        columns[0] = (state >> 12) & 0xF;
        columns[1] = (state >> 8) & 0xF;
        columns[2] = (state >> 4) & 0xF;
        columns[3] = state & 0xF;

        int result[4];
        result[0] = multiply(matrix[0][0], columns[0]) ^ multiply(matrix[0][1], columns[1]);
        result[1] = multiply(matrix[1][0], columns[0]) ^ multiply(matrix[1][1], columns[1]);
        result[2] = multiply(matrix[0][0], columns[2]) ^ multiply(matrix[0][1], columns[3]);
        result[3] = multiply(matrix[1][0], columns[2]) ^ multiply(matrix[1][1], columns[3]);
        return (result[0] << 12) | (result[1] << 8) | (result[2] << 4) | result[3];
    }

    static int multiply(int a, int b) {
        // 列混淆计算
        int result = 0;
        while (b != 0) {
            if ((b & 0x01) != 0) {
                result ^= a;
            }
            bool carry = (a & 0x08) != 0;
            a <<= 1;
            if (carry) {
                a ^= 0x13;
            }
            b >>= 1;
        }
        return result;
    }

    static int rcon(int round) {
        // 轮常量计算
        if (round == 1) {
            return 0x80;
        }
        else if (round == 2) {
            return 0x30;
        }
        else {
            return 0;
        }
    }

    static int g(int w, int round) {
        // 密钥扩展
        int n0_ = S_BOX[(w >> 6) & 0x03][(w >> 4) & 0x03];
        int n1_ = S_BOX[(w >> 2) & 0x03][w & 0x03];
        int result = n0_ | (n1_ << 4);
        return rcon(round) ^ result;
    }

    static int* expandKey(int key) {
        // 生成轮密钥
        int* roundKey = new int[3];
        roundKey[0] = key;
        for (int i = 1; i < 3; i++) {
            roundKey[i] = generateRoundKey(roundKey[i - 1], i);
        }
        return roundKey;
    }

    static int generateRoundKey(int roundKey, int round) {
        int result = roundKey;
        int w0 = (result >> 8) & 0xFF;
        int w1 = result & 0xFF;
        int w2 = w0 ^ g(w1, round);
        int w3 = w2 ^ w1;
        return (w2 << 8) ^ w3;
    }

public:
    // 加密和解密函数
    static int encrypt1(int plaintext, int key) {
        int* roundKey = expandKey(key);
        int state = plaintext;
        state = addRoundKey(state, roundKey[0]);
        for (int i = 0; i < 2; i++) {
            state = substituteBytes(state, S_BOX);
            state = rowShift(state);
            if (i < 1) {
                state = mixColumns(state, MIX_COLUMNS_MATRIX);
            }
            state = addRoundKey(state, roundKey[i + 1]);
        }
        return state;
    }

    static int decrypt1(int ciphertext, int key) {
        int* roundKey = expandKey(key);
        int state = ciphertext;
        state = addRoundKey(state, roundKey[2]);
        for (int i = 1; i >= 0; i--) {
            if (i < 1) {
                state = mixColumns(state, INVERSE_MIX_COLUMNS_MATRIX);
            }
            state = rowShift(state);
            state = substituteBytes(state, INVERSE_S_BOX);
            state = addRoundKey(state, roundKey[i]);
        }
        return state;
    }

    // ASCII和二进制转换函数
    static std::bitset<16> asciiToBinary(const std::string& asciiText) {
        if (asciiText.length() < 2) {
            std::cerr << "Invalid ASCII text. Length should be at least 2 characters." << std::endl;
            return std::bitset<16>(0);
        }
        int num = static_cast<int>(static_cast<unsigned char>(asciiText[0])) << 8;
        num += static_cast<int>(static_cast<unsigned char>(asciiText[1]));
        return std::bitset<16>(num);
    }

    static std::string binaryToAscii(const std::bitset<16>& binary) {
        int num = static_cast<int>(binary.to_ulong());
        char c1 = (num >> 8) & 0xFF;
        char c2 = num & 0xFF;
        return std::string(1, c1) + std::string(1, c2);
    }

};

// 常量的定义
const int SAES::S_BOX[4][4] = {
        {0x9, 0x4, 0xA, 0xB},
        {0xD, 0x1, 0x8, 0x5},
        {0x6, 0x2, 0x0, 0x3},
        {0xC, 0xE, 0xF, 0x7}
};

const int SAES::INVERSE_S_BOX[4][4] = {
        {0xA, 0x5, 0x9, 0xB},
        {0x1, 0x7, 0x8, 0xF},
        {0x6, 0x0, 0x2, 0x3},
        {0xC, 0x4, 0xD, 0xE}
};

const int SAES::MIX_COLUMNS_MATRIX[2][2] = {
        {0x1, 0x4},
        {0x4, 0x1}
};

const int SAES::INVERSE_MIX_COLUMNS_MATRIX[2][2] = {
        {0x9, 0x2},
        {0x2, 0x9}
};

void figure::on_pushButton_clicked()
{
    QString text1= ui->lineEdit->text();
    QString text2= ui->lineEdit_2->text();
    QString text3= ui->lineEdit_3->text();
    char*  ch;
    QByteArray ba = text1.toLatin1(); // must
    ch=ba.data();
    char*  ch2;
    QByteArray ba2 = text2.toLatin1(); // must
    ch2=ba2.data();
    char*  ch3;
    QByteArray ba3 = text3.toLatin1(); // must
    ch3=ba3.data();
    if(text1.length()==0)
    {
        if(text2.length()!=16)
        {
            QMessageBox::information(NULL, "错误", "你输入的秘钥长度不正确", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
        else
        {
            for(int i=0;i<text2.length();i++)
            {
              if(ch2[i]!='0'&&ch2[i]!='1')
              {
                  QMessageBox::information(NULL, "错误", "你输入的秘钥不是二进制", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
              }
            }
            if(text3.length()!=16)
            {
                QMessageBox::information(NULL, "错误", "你输入的密文长度不正确", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }
            else
            {
                bool w=true;
                for(int i=0;i<text3.length();i++)
                {
                  if(ch3[i]!='0'&&ch3[i]!='1')
                  {
                      w=false;
                      QMessageBox::information(NULL, "错误", "你输入的密文不是二进制", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                  }
                }
                if(w)
                {
                    vector<int> encrypted = {}; // 16位明文
                    vector<int> key = {}; // 16位密钥
                    for(int i=0;i<text3.length();i++)
                    {
                        encrypted.push_back(int(ch3[i])-48);
                    }
                    for(int i=0;i<text2.length();i++)
                    {
                        key.push_back(int(ch2[i])-48);
                    }
                    stringstream ss;
                    string str;
                    copy(encrypted.begin(), encrypted.end(), ostream_iterator<int>(ss, ""));
                    str = ss.str();
                    ss.str("");
                    bitset<16> encryptedbits(str);
                    copy(key.begin(), key.end(), ostream_iterator<int>(ss, ""));
                    str = ss.str();
                    ss.str("");
                    bitset<16> keybits(str);
                    int encryptedbitsword = static_cast<int>(encryptedbits.to_ulong());
                    int keyword = static_cast<int>(keybits.to_ulong());
                    int decrypted = SAES::decrypt1(encryptedbitsword, keyword);
                    bitset<16> decryptedbits(decrypted);
                    str=decryptedbits.to_string();
                    QString qstr = QString::fromStdString(str);
                    ui->lineEdit->setText(qstr);
                }
            }
        }
    }
    else
    {
        if(text1.length()!=16)
        {
            QMessageBox::information(NULL, "错误", "你输入的明文长度不正确", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
        else
        {
            for(int i=0;i<text1.length();i++)
            {
              if(ch[i]!='0'&&ch[i]!='1')
              {
                  QMessageBox::information(NULL, "错误", "你输入的明文不是二进制", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
              }
            }
            if(text2.length()!=16)
            {
                QMessageBox::information(NULL, "错误", "你输入的秘钥长度不正确", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }
            else
            {
                bool w=true;
                for(int i=0;i<text2.length();i++)
                {
                  if(ch2[i]!='0'&&ch2[i]!='1')
                  {
                      w=false;
                      QMessageBox::information(NULL, "错误", "你输入的秘钥不是二进制", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                  }
                }
                if(w)
                {
                    vector<int> plaintext = {}; // 16位明文
                    vector<int> key = {}; // 16位密钥
                    for(int i=0;i<text1.length();i++)
                    {
                        plaintext.push_back(int(ch[i])-48);
                    }
                    for(int i=0;i<text2.length();i++)
                    {
                        key.push_back(int(ch2[i])-48);
                    }
                    stringstream ss;
                    string str;
                    copy(plaintext.begin(), plaintext.end(), ostream_iterator<int>(ss, ""));
                    str = ss.str();
                    ss.str("");
                    bitset<16> plaintextbits(str);
                    copy(key.begin(), key.end(), ostream_iterator<int>(ss, ""));
                    str = ss.str();
                    qDebug()<<QString::fromStdString(str);
                    ss.str("");
                    bitset<16> keybits(str);
                    int plaintextbitsword = static_cast<int>(plaintextbits.to_ulong());
                    int keyword = static_cast<int>(keybits.to_ulong());
                    int encrypted = SAES::encrypt1(plaintextbitsword, keyword);
                    bitset<16> encryptedbits(encrypted);
                    str=encryptedbits.to_string();
                    QString qstr = QString::fromStdString(str);
                    ui->lineEdit_3->setText(qstr);
                }
            }
        }
    }
}
void figure::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(e->x()>840&&e->x()<840+110&&e->y()>10&&e->y()<10+60)
        {
            this->close();
            choice *f=new choice();
            f->show();
        }
    }
}

#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    QStringList styles;
    styles.append(QStyleFactory::keys());

    foreach(QString stl, styles)
        qDebug() << stl;

    QDirIterator it(":/styles", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        styles.append(it.fileInfo().baseName());
        stylesPath.append(it.filePath());
    }

    this->setWindowTitle(tr("Settings"));

    ui->comboStylesBox->addItems(styles);
    ui->comboStylesBox->setCurrentIndex(2);

    /*Screen Recording*/
    ui->spinBoxThread->setRange(1, QThread::idealThreadCount());
    ui->spinBoxQualityValue->setRange(0, 100);
    ui->spinBoxQualityValue->setDisabled(true);
    ui->spinBoxSetFps->setRange(1, 120);
    ui->spinBoxSetFps->setValue(25);
    ui->spinBoxSetFps->setDisabled(true);
    ui->spinBoxLockFps->setRange(1, 120);
    ui->spinBoxLockFps->setValue(25);
    ui->spinBoxLockFps->setDisabled(true);

    m_codecList << "1978" << "2VUY" << "3IV0" << "3IV1" << "3IV2" << "3IVD" << "3IVX" << "8BPS" << "AAS4" << "AASC" << "ABYR" << "ACTL" << "ADV1"
                << "ADVJ" << "AEIK" << "AEMI" << "AFLC" << "AFLI" << "AHDV" << "AJPG" << "AMPG" << "ANIM" << "AP41" << "AP42" << "ASLC" << "ASV1"
                << "ASV2" << "ASVX" << "ATM4" << "AUR2" << "AURA" << "AVC1" << "AVRN" << "BA81" << "BINK" << "BLZ0" << "BT20" << "BTCV" << "BW10"
                << "BYR1" << "BYR2" << "CC12" << "CDVC" << "CFCC" << "CGDI" << "CHAM" << "CJPG" << "CMYK" << "CPLA" << "CRAM" << "CSCD" << "CTRX"
                << "CVID" << "CWLT" << "CXY1" << "CXY2" << "CYUY" << "D261" << "D263" << "DAVC" << "DCL1" << "DCL2" << "DCL3" << "DCL4" << "DCL4"
                << "DIV3" << "DIV4" << "DIV5" << "DIVX" << "DM4V" << "DMB1" << "DMB2" << "DMK2" << "DSVD" << "DUCK" << "DV25" << "DV50" << "DVAN"
                << "DVCS" << "DVE2" << "DVH1" << "DVHD" << "DVSD" << "DVSL" << "DVX1" << "DVX2" << "DVX3" << "DX50" << "DXGM" << "DXTC" << "DXTN"
                << "EKQ0" << "ELK0" << "EM2V" << "ES07" << "ESCP" << "ETV1" << "ETV2" << "ETVC" << "FFV1" << "FLJP" << "FMP4" << "FMVC" << "FPS1"
                << "FRWA" << "FRWD" << "FVF1" << "GEOX" << "GJPG" << "GLZW" << "GPEG" << "GWLT" << "H260" << "H261" << "H262" << "H263" << "H264"
                << "H265" << "H266" << "H267" << "H268" << "H269" << "HDYC" << "HEVC" << "HFYU" << "HMCR" << "HMRR" << "I263" << "ICLB" << "IGOR"
                << "IJLV" << "IJPG" << "ILVC" << "ILVR" << "IPDV" << "IPMA" << "IR21" << "IRAW" << "ISME" << "IV30" << "IV31" << "IV32" << "IV33"
                << "IV34" << "IV35" << "IV36" << "IV37" << "IV38" << "IV39" << "IV40" << "IV41" << "IV42" << "IV43" << "IV44" << "IV45" << "IV46"
                << "IV47" << "IV48" << "IV49" << "IV50" << "JBYR" << "JPEG" << "JPGL" << "KB2A" << "KB2D" << "KB2F" << "KB2G" << "KMVC" << "L261"
                << "L263" << "LBYR" << "LCMW" << "LCW2" << "LEAD" << "LGRY" << "LJ11" << "LJ22" << "LJ2K" << "LJ44" << "LJPG" << "LMP2" << "LMP4"
                << "LSVC" << "LSVX" << "LZO1" << "M261" << "M263" << "M4CC" << "M4S2" << "MC12" << "MCAM" << "MJ2C" << "MJPG" << "MMES" << "MP2A"
                << "MP2T" << "MP2V" << "MP42" << "MP43" << "MP4A" << "MP4S" << "MP4T" << "MP4V" << "MPEG" << "MPG4" << "MPGI" << "MR16" << "MRCA"
                << "MRLE" << "MSVC" << "MSZH" << "MTX1" << "MTX2" << "MTX3" << "MTX4" << "MTX5" << "MTX6" << "MTX7" << "MTX8" << "MTX9" << "MVI1"
                << "MVI2" << "MWV1" << "NAVI" << "NDSC" << "NDSM" << "NDSP" << "NDSS" << "NDXC" << "NDXH" << "NDXP" << "NDXS" << "NHVU" << "NI24"
                << "NTN1" << "NTN2" << "NVDS" << "NVH2" << "NVS0" << "NVS1" << "NVS2" << "NVS3" << "NVS4" << "NVS5" << "NVT0" << "NVT1" << "NVT2"
                << "NVT3" << "NVT4" << "NVT5" << "PDVC" << "PGVV" << "PHMO" << "PIM1" << "PIM2" << "PIMJ" << "PIXL" << "PJPG" << "PVEZ" << "PVMM"
                << "PVW2" << "QPEG" << "QPEQ" << "RGBT" << "RLE " << "RLE4" << "RLE8" << "RMP4" << "RPZA" << "RT21" << "RV20" << "RV30" << "RV40"
                << "S422" << "SAN3" << "SDCC" << "SEDG" << "SFMC" << "SMK2" << "SMK4" << "SMKA" << "SMP4" << "SMSC" << "SMSD" << "SMSV" << "SP40"
                << "SP44" << "SP54" << "SPIG" << "SQZ2" << "STVA" << "STVB" << "STVC" << "STVX" << "STVY" << "SV10" << "SVQ1" << "SVQ3" << "TLMS"
                << "TLST" << "TM20" << "TM2X" << "TMIC" << "TMOT" << "TR20" << "TSCC" << "TV10" << "TVJP" << "TVMJ" << "TY0N" << "TY2C" << "TY2N"
                << "UCOD" << "ULTI" << "V210" << "V261" << "V655" << "VCR1" << "VCR2" << "VCR3" << "VCR4" << "VCR5" << "VCR6" << "VCR7" << "VCR8"
                << "VCR9" << "VDCT" << "VDOM" << "VDOW" << "VDTZ" << "VGPX" << "VIDS" << "VIFP" << "VIVO" << "VIXL" << "VLV1" << "VP30" << "VP31"
                << "VP40" << "VP50" << "VP60" << "VP61" << "VP62" << "VP70" << "VP80" << "VQC1" << "VQC2" << "VQJC" << "VSSV" << "VUUU" << "VX1K"
                << "VX2K" << "VXSP" << "VYU9" << "VYUY" << "WBVC" << "WHAW" << "WINX" << "WJPG" << "WMV1" << "WMV2" << "WMV3" << "WMVA" << "WNV1"
                << "WVC1" << "X263" << "X264" << "XLV0" << "XMPG" << "XVID" << "XWV0" << "XWV1" << "XWV2" << "XWV3" << "XWV4" << "XWV5" << "XWV5"
                << "XWV6" << "XWV7" << "XWV8" << "XWV9" << "XXAN" << "Y16 " << "Y411" << "Y41P" << "Y444" << "Y8  " << "YC12" << "YUV8" << "YUV9"
                << "YUVP" << "YUY2" << "YUYV" << "YV12" << "YV16" << "YV92" << "ZLIB" << "ZMBV" << "ZPEG" << "ZYGO" << "ZYYY";

    foreach(QString codec, m_codecList)
        ui->comboBoxCodec->addItem(codec);

    ui->comboBoxCodec->setCurrentIndex(192);
    /*Screen Recording*/
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

const Setting &OptionsDialog::getSettings() const
{
    return m_setting;
}

void OptionsDialog::setSettings(const Setting &settings)
{
    m_setting = settings;
    ui->checkBoxCoverSH->setChecked(m_setting.isCoverSlideshowEnabled);
    ui->checkBoxMediaSH->setChecked(m_setting.isMediaSlideshowEnabled);
    ui->checkBoxFullscreen->setChecked(m_setting.isFullscreen);
    ui->spinBoxMediaSH->setValue(m_setting.mediaSlideshowRate);
    ui->spinBoxCoversSH->setValue(m_setting.coverSlideshowRate);
    ui->comboStylesBox->setCurrentIndex(m_setting.styleNumber);
    ui->spinBoxThread->setValue(m_setting.threadCount);
    ui->checkBoxQuality->setChecked(m_setting.isCustomQualityEnabled);
    ui->spinBoxQualityValue->setValue(m_setting.frameQuality);
    ui->checkBoxSetFps->setChecked(m_setting.isFpsSetEnabled);
    ui->checkBoxLockFps->setChecked(m_setting.isFpsLockEnabled);
    ui->spinBoxSetFps->setValue(m_setting.fpsSet);
    ui->spinBoxLockFps->setValue(m_setting.fpsLock);
    ui->comboBoxCodec->setCurrentIndex(m_setting.codecIndex);
}

void OptionsDialog::on_comboStylesBox_currentIndexChanged(int index)
{
    qDebug() << "Style Index:" << index;
    qApp->setStyleSheet(styleSheet());
    QApplication::setStyle(QStyleFactory::create(ui->comboStylesBox->itemText(2)));
    if(index < 3)
    {
        QApplication::setStyle(QStyleFactory::create(ui->comboStylesBox->itemText(index)));
    }
    else
    {
        QFile file(stylesPath.at(index - 3));
        file.open(QFile::ReadOnly);
        QString str = QLatin1String(file.readAll());
        qApp->setStyleSheet(str);
    }
}

void OptionsDialog::on_buttonBox_accepted()
{
    m_setting.isFullscreen = ui->checkBoxFullscreen->isChecked();
    m_setting.isCoverSlideshowEnabled = ui->checkBoxCoverSH->isChecked();
    m_setting.isMediaSlideshowEnabled = ui->checkBoxMediaSH->isChecked();
    m_setting.styleNumber = ui->comboStylesBox->currentIndex();
    m_setting.mediaSlideshowRate = ui->spinBoxMediaSH->value();
    m_setting.coverSlideshowRate = ui->spinBoxCoversSH->value();

    m_setting.isCustomQualityEnabled = ui->checkBoxQuality->isChecked();
    m_setting.isFpsSetEnabled = ui->checkBoxSetFps->isChecked();
    m_setting.isFpsLockEnabled = ui->checkBoxLockFps->isChecked();
    m_setting.fpsSet = ui->spinBoxSetFps->value();
    m_setting.fpsLock = ui->spinBoxLockFps->value();
    m_setting.frameQuality = ui->spinBoxQualityValue->value();
    m_setting.codec = ui->comboBoxCodec->currentText();
    m_setting.codecIndex = ui->comboBoxCodec->currentIndex();
    m_setting.threadCount = ui->spinBoxThread->value();
}

void OptionsDialog::on_checkBoxQuality_stateChanged(int arg1)
{
    qDebug() << "Qualit Check Box Clicked";
    if(!arg1)
        ui->spinBoxQualityValue->setDisabled(true);
    else if(arg1 == 2)
        ui->spinBoxQualityValue->setEnabled(true);
}

void OptionsDialog::on_checkBoxSetFps_stateChanged(int arg1)
{
    qDebug() << "Set FPS Clicked";
    if(!arg1)
        ui->spinBoxSetFps->setDisabled(true);
    else if(arg1 == 2)
        ui->spinBoxSetFps->setEnabled(true);
}

void OptionsDialog::on_checkBoxLockFps_stateChanged(int arg1)
{
    qDebug() << "Lock FPS Clicked";
    if(!arg1)
        ui->spinBoxLockFps->setDisabled(true);
    else if(arg1 == 2)
        ui->spinBoxLockFps->setEnabled(true);
}

#define DEFAULT_WAKEUP	50
#define DEFAULT_BATCH_COUNT 25

static const int MAX_PORTS	   = 16;
static const int max_registers = 256;

static int add_lrc_and_cr(char * buf,int len);

enum SECTION_TYPE{
	ost_dm_section=0,
	ost_hr_section=1,
	ost_ir_section=2,
	ost_max_section=3,
};

class COmronDevice;

class OMRON_SECTION{
public:	
	OMRON_SECTION(SECTION_TYPE t);
	int read_section_phase_1();
	void read_section_phase_2();
	__bool write_register(PCRTK_TAG tte, PCTAG_VALUE tv);
	__bool write_bit(__uint wordAddr, __uint bitAddr, __bool value);
	void update_tag(PCRTK_TAG tte, struct pmc_value_t  & pt);
	int invalidate_cache();
	int update_cache(char * buf,int len);
	void comm_fault_handler();
protected:
	int check_error(char * buf);
	inline bool is_dm_section()
	{
		return ost_dm_section == m_sectionType? true : false;
	}
	void check_state();
public:
	SECTION_TYPE m_sectionType;
	int	 m_nRegisters;
	class COmronDevice * m_parent;
protected:
	char *m_writeCmdPrefix;
	char *m_readCmdPrefix;
	int	 m_curRegister;
	int	 m_lastReadRegisters;;
	int	 m_failCount;
	char m_cache[max_registers];
	bool m_cacheFlags[max_registers];
	//int hbuf_length;
};

class DM_SECTION : public OMRON_SECTION
{
public:
	DM_SECTION () : OMRON_SECTION(ost_dm_section)
	{
		config();
	}
	void config(int c_regs=200, int delay=150)
	{
		if(c_regs>200 || c_regs<0) c_regs=200;
		m_nRegisters=c_regs;		
	}
};

class HR_SECTION : public OMRON_SECTION{
public:
	HR_SECTION () : OMRON_SECTION(ost_hr_section)
	{
		config();
	};
	void config(int c_regs=100,int delay=150)
	{
		if(c_regs>100 || c_regs<0) c_regs=100;
		m_nRegisters=c_regs;
	}
};

class IR_SECTION : public OMRON_SECTION{
public:
	IR_SECTION () : OMRON_SECTION (ost_ir_section)
	{
		config();
	}
	void config(int c_regs=60, int delay=150)
	{
		if(c_regs>60 || c_regs<0) c_regs=60;
		m_nRegisters=c_regs;
	}
};

class COmronDevice : public CPeriodicThread
{
public:
	DM_SECTION		dmSection;
	HR_SECTION		hrSection;
	IR_SECTION		irSection;
	OMRON_SECTION	*m_pSections[3];
	int				m_iDelay[3];
	int				m_iWakeup;
	int				m_iCurrentSection;
	int				m_iPortNo;
	int				m_iUnitNo;
	PDEVICE_INFO	m_Handle;
	int				m_iBatchCount;
	
	enum device_type_t{
		c200_device,
		c1000_device,
		c2000_device
	}m_deviceType;
	
	enum device_mode_t{
		unknown_mode,
		run_mode,
		monitor_mode,
		program_mode,
	};
public:
	COmronDevice(int pno)
	{
		m_pSections[0] = &dmSection;
		m_pSections[1] = &hrSection;
		m_pSections[2] = &irSection;
		m_iPortNo = pno;
		m_iCurrentSection = 0;
	}
	int config(int c, char **v);
	device_mode_t get_mode();
	void set_mode(device_mode_t newMode);
private:
	virtual void pre_run();
	virtual void task(); 
};


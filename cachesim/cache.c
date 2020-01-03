#include "common.h"
#include <inttypes.h>

struct cache_unit {
    bool valid;
	bool dirty;
	uint8_t tag;
    uint8_t block[BLOCK_SIZE];
};

struct cache_unit cache[256];

// 从块号为‘block_num’的内存地址中读出一整个cache块大小的内容到‘buf’中
void mem_read(uintptr_t block_num, uint8_t *buf);

// 往块号为‘block_num’的内存地址中写入一整个cache块大小的内容‘buf’
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions

// 从cache中读出‘addr’地址处的四字节数据
// 若缺失，需先从内存读入数据
uint32_t cache_read(uintptr_t addr) {
	bool hit = false; //用于判断是否命中
	uint32_t result = 0; //用于存放返回结果
	bool full = false; //用于判断对应的组(set)内是否已满
	uint16_t mem_block_NO = 0; //用于记录主存块号

	uint8_t block_inside_offset = (addr & 0x3f); //用于记录块内偏移量
	uint8_t index = ((addr >> 6) & 0x3f); //用于cache组号
	uint8_t tag = ((addr >> 12) & 0xff); //用于记录块群号
	mem_block_NO = ((mem_block_NO + tag) << 8)+index;

    for(int i = 0; i < 4; i ++) {
	    if(cache[index*4+i].tag == tag &&  cache[index*4+i].valid == true) {
		    hit = true;
			for(int j = 4; j > 0; j --) {
			    result += (cache[index*4+i].block[block_inside_offset+j] << (j-1)*8);
			}
            break;
		}
	}
    
	if(hit == false) { //未命中，访问内存
		full = cache[index*4].valid && cache[index*4+1].valid && cache[index*4+2].valid && cache[index*4+3].valid; //先检查对应的cache组是否满了
		if(full == true) {
		    uint8_t random_select = rand() % 4; //满了随机选择一个替换
			if(cache[index*4+random_select].dirty == true) {
				uint16_t old_mem_block_NO = 0;
				old_mem_block_NO = ((old_mem_block_NO + cache[index*4+random_select].tag) << 8)+index; //计算将要被替换的一块所对应的主存块号
				mem_write(old_mem_block_NO, &(cache[index*4+random_select].block[0])); //回写
			}
		    mem_read(mem_block_NO, &(cache[index*4+random_select].block[0]));
			cache[index*4+random_select].valid = true;
			cache[index*4+random_select].dirty = false; //完成从内存读取替换

			for(int j = 4; j > 0; j --) {
			    result += (cache[index*4+random_select].block[block_inside_offset+j] << (j-1)*8);
			}

		}
		else {
		    for(int i = 0; i < 4; i ++) {
		        if(cache[index*4+i].valid == false) {
			        mem_read(mem_block_NO, &(cache[index*4+i].block[0]));
				    cache[index*4+i].valid = true;
			        for(int j = 4; j > 0; j --) {
			            result += (cache[index*4+i].block[block_inside_offset+j] << (j-1)*8);
			        }
				    break;
			    }
		    }
		}

	
	}

  return result;
}

// 往cache中‘addr’地址所属的块写入数据‘data’，写掩码为‘wmask’
// 例如当‘wmask’为‘0xff’时，只写入低8比特
// 若缺失，需先从内存中读入数据
void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
	/*
	bool hit = false; //用于判断是否命中
	uint32_t result = 0; //用于存放返回结果
	bool full = false; //用于判断对应的组(set)内是否已满
	uint16_t mem_block_NO = 0; //用于记录主存块号

	uint8_t block_inside_offset = (addr & 0x3f); //用于记录块内偏移量
	uint8_t index = ((addr >> 6) & 0x3f); //用于cache组号
	uint8_t tag = ((addr >> 12) & 0xff); //用于记录块群号
	mem_block_NO = ((mem_block_NO + tag) << 8)+index;

    for(int i = 0; i < 4; i ++) {
	    if(cache[index*4+i].tag == tag &&  cache[index*4+i].valid == true) {
		    hit = true;
            

			for(int j = 0; j < 4; j ++) {
			    result += (cache[index*4+i].block[block_inside_offset+j] << j*4);
			}
            break;
		}
	}
*/

}

// 初始化一个数据大小为‘2^total_size_width'B，关联度为’2^associativity_width‘
// 例如’init_cache(14, 2)'将初始化一个16KB，4路组相联的cache
// 将所有的valid bit置为无效即可
void init_cache(int total_size_width, int associativity_width) {
	//int size = (exp2(total_size_width) / BLOCK_SIZE);

	for(int i = 0; i < 256; i++) {
	    cache[i].valid = false;
	}
}

void display_statistic(void) {

}

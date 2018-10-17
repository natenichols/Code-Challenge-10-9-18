/*
 * author: iancain
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <memory.h>
#include <memory_pool.h>


// PRIVATE: declared inside *.c file
typedef struct memory_pool_block_header
{
    uint32_t magic;      // NODE_MAGIC = 0xBAADA555
    size_t size;
    bool inuse;      // true = currently allocated

    struct memory_pool_block_header * next;

} memory_pool_block_header_t;

struct memory_pool {
    size_t count;         // total elements
    size_t block_size;   // size of each block
    size_t available;

    struct memory_pool_block_header * pool;
    //points to the last block for to add to the back
    struct memory_pool_block_header * tail;
};

//---
// MACROS
//

// HTODB = header to data block
//     converts header pointer to container data block
//
#define MEMORY_POOL_HTODB(_header_, _block_size_) ((void *)_header_ - _block_size_)

// DBTOH = data block to header
//     convert data block pointer to point to embedded header information block
//
#define MEMORY_POOL_DBTOH(_data_block_, _block_size_) ((memory_pool_block_header_t *)(_data_block_ + _block_size_))

// magic value to check for data corruption
#define NODE_MAGIC 0xBAADA555

memory_pool_t * memory_pool_init(size_t count, size_t block_size)
{
    memory_pool_t *mp = NULL;
    memory_pool_block_header_t * last;
    void * block = NULL;
    int n = 0;

    // allocate memory pool struct. give ownership back to caller
    mp = (memory_pool_t*) malloc (sizeof(memory_pool_t));
    if( mp == NULL ) {
        printf("ERROR: memory_pool_destroy: unable to malloc memory_pool_t. OOM\n");
        return NULL;
    }

    mp->pool = NULL;
    mp->block_size = 0;
    mp->available = 0;
    mp->count = 0;

    void* next_block;
    for( n = 0; n < count; ++n ) {
        // allocate data block
        //   data block size + header siz
        //
        size_t total_size = block_size + sizeof(memory_pool_block_header_t);
	
	block = malloc(total_size);

	// move to end of data block to create header
        //
	
	memory_pool_block_header_t * header = MEMORY_POOL_DBTOH(block, block_size);
	
	//update the information in the header.
	header->size = block_size;
	header->next = next_block;
	header->inuse = false;

	//keep track of which header each header->next should be pointing to
	next_block = header;

	// add to stack (just a simple stack)
	if(n == 0){
		mp->tail = header;
		header->next = NULL;
	}
	if(n == count - 1){
		//mp->pool points to the top of the data block at the top of the stack
		mp->pool =  (memory_pool_block_header_t*) block;
	}
    
        

        printf("MEMORY_POOL: i=%d, data=%p, header=%p, block_size=%zu, next=%p\n",
               n, block, header, header->size, header->next);
	block += sizeof(memory_pool_block_header_t);

    }

    printf("memory_pool_init(mp=%p, count=%zu, block_size=%zu)\n", mp, count, block_size);

    
    mp->count = count;
    mp->block_size = block_size;
    mp->available = count;
   
    return n == count ? mp : NULL;
}

bool memory_pool_destroy(memory_pool_t * mp)
{

    printf("memory_pool_destroy(mp = %p, count=%zu, block_size=%zu)\n", mp, mp->count, mp->block_size);

    //!!!This code is ugly, come back to it.
    for(int n = 0; n < mp->count; ++n ) {
	if(n != mp->count -1){

		memory_pool_block_header_t * temp = MEMORY_POOL_DBTOH((void*)mp->pool, mp->block_size)->next;

		free((void*)mp->pool);

		mp->pool = (memory_pool_block_header_t*) MEMORY_POOL_HTODB(temp, mp->block_size);	
		
	}
	else{
		free((void*)mp->pool);
	}
    }
   

    // free memory pool itself
    free(mp);

    return true;
}

void * memory_pool_acquire(memory_pool_t * mp)
{
    //if there is not available memory, there is no memory to acquire. 
    if(mp->available == 0)
	return NULL;

    //pop stack
    memory_pool_block_header_t * header = MEMORY_POOL_DBTOH((void*)mp->pool, mp->block_size);
 
    
    //get data block from header
    void * data = mp->pool;
   
    //return data;  // return to caller
    if(header->inuse == false){
		mp->available--;
	
		if(mp->available == 0){
			mp->pool = NULL;
			mp->tail = NULL;
		}
		else{
			//pool is equal to the next block in the stack
			mp->pool = MEMORY_POOL_HTODB(header->next, mp->block_size);
		}

		
		header->inuse = true;
		return data;
    }
    else{
	return NULL;
    }
}

bool memory_pool_release(memory_pool_t *mp, void * data)
{
    // move to header inside memory block using MEMORY_POOL_DBTOH(data, mp->block_size)
    memory_pool_block_header_t * header = MEMORY_POOL_DBTOH(data, mp->block_size);

    printf("memory_pool_release: data=%p, header=%p, block_size=%zu, next=%p\n",
           data, header, header->size, header->next);

    if(!header->inuse)
	return false;	

    if(mp->available == 0){
	mp->pool = data;
	mp->tail = header;
    }
    else{

     
	//Adds the header to the bottom of the stack (changes the next pointer of the current tail block)
	mp->tail->next = header;

	//Points tail to new bottom of the stack (changes the tail pointer associated with pool)
	mp->tail = header;

	//Sets last blocks next pointer to null
	mp->tail->next = NULL;
	
    }
    header->inuse = false;
    mp->available ++;
    return true;
}

size_t memory_pool_available(memory_pool_t *mp)
{
    if( mp == NULL ) {
        printf("ERROR: memory_pool_available: memory pool invalid\n");
        return 0;
    }
    return mp->available;
}

void memory_pool_dump(memory_pool_t *mp)
{
    if( mp == NULL ) {
        printf("ERROR: memory_pool_dump: memory pool invalid\n");
        return;
    }
    printf("memory_pool_dump(mp = %p, count=%zu, available=%zu, block_size=%zu)\n",
            mp, mp->count, mp->available, mp->block_size);

    memory_pool_block_header_t * header = MEMORY_POOL_DBTOH((void*)mp->pool, mp->block_size);

    for(int n = 0; n < mp->available; ++n ) {
        void * data_block = MEMORY_POOL_HTODB(header,mp->block_size);
        printf(" + block: i=%d, data=%p, header=%p, inuse=%s, block_size=%zu, next=%p\n",
               n, data_block, header, header->inuse ? "TRUE":"FALSE", header->size, header->next);

        header = header->next;
    }
}

#define OVERLOAD  __attribute__((overloadable))

#define THREAD_ID           get_global_id(0)
#define THREAD_LENGTH       get_global_size(0)
#define THREAD_LOCAL_ID     get_local_id(0)
#define THREAD_LOCAL_LENGTH get_local_size(0)
#define GROUP_ID            get_group_id(0)
#define GROUP_LENGTH        get_num_groups(0)

#define isEven(value) value % 2 == 0
#define isOdd(value)  value % 2 != 0


#define ENV_64BITS
#ifdef ENV_64BITS
    #pragma OPENCL EXTENSION cl_khr_int64_base_atomics: enable
#endif

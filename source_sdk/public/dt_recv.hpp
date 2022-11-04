
#ifndef CSGO_CHEAT_DT_RECV_HPP
#define CSGO_CHEAT_DT_RECV_HPP

struct RecvTable;

struct RecvProp
{
	char *var_name;
	int recv_type;
	int flags;
	int string_buffer_size;
	bool inside_array;
	void *extra_data;
	RecvProp *array_prop;
	void *array_length_proxy;
	void *proxy_fn;
	void *datatable_proxy_fn;
	RecvTable *datatable;
	int offset;
	int element_stride;
	int num_elements;
	char *parent_array_prop_name;
};

struct RecvTable
{
	RecvProp *props;
	int prop_count;
	void *decoder;
	char *net_table_name;
	bool is_initialized;
	bool in_main_list;
};

#endif //CSGO_CHEAT_DT_RECV_HPP

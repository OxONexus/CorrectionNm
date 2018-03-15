/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 16:10:01 by apaget            #+#    #+#             */
/*   Updated: 2018/03/15 17:30:13 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <ar.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"

typedef struct					s_symbol
{
	char						symb;
	char						*name;
	uint64_t					addr;
}								t_symbol;

typedef struct					s_program
{
	int							load_size;
	void						*header;
	void						*start_prog;
	int							magic_number;
	struct load_command			*loadcmd;
	int							nb_loadcmds;
	struct symtab_command		*symtabcmds;
	int							nb_symtabcmds;
	struct nlist_64				*symtab_array;
	struct nlist				*symtab_array2;
	char						*start_stringtable;
	struct segment_command_64	*segcmds;
	unsigned int				endian;
	struct section				**section;
	int							nbsection;
	struct section_64			**section_64;
	int							nbsection_64;
}								t_program;

void							lst_add(t_list **begin, void *content,
		int content_size);
void							read_header_32(t_program *prog, char *ptr);
void							read_header_64(t_program *prog, char *ptr);
void							*find_load_command(t_program *prog, char *ptr, int nb_loadcmds,
		unsigned int cmd);
t_list							*get_sym_list(t_program *prog, char *ptr);
unsigned long long				llendian_read(t_program *prog,
		unsigned long long x);
unsigned long long				llendian_swap(unsigned long long x);
unsigned long					endian_read(t_program *prog, unsigned long x);
unsigned long					endian_swap(unsigned long x);
void							direct(t_program *prog, char *ptr, char *file);
t_list							*get_sym_list_32(t_program *prog, char *ptr);
void							check_data(t_program *prog);
char							get_symb(t_program *prog, int i);
char							get_symb32(t_program *prog, int i);
t_list							*get_sym_list(t_program *prog, char *ptr);
void							print_list(t_program *prog, t_list *list, int type, int print0);
void							read_ar_header(t_program *prog, char *ptr);
void							read_fat_head(t_program *prog, char *ptr);
void							oread_fat_head(t_program *prog, char *ptr);
void							oread_header_64(t_program *prog, char *ptr);
void							oread_header_32(t_program *prog, char *ptr);
void							odirect(t_program *prog, char *ptr, char *file);
void							*find_sub_segment(char *ptr, t_program *prog,
								unsigned int nb_segment, char *seg);
void							*find_sub_segment32(char *ptr, t_program *prog,
		unsigned int nb_segment, char *seg);
void							oread_fat_head(t_program *prog, char *ptr);
void							*find_load_command(t_program *prog, char *ptr, int nb_loadcmds,
		unsigned int cmd);
void							*jerecherche(char *ptr, int nsect, char *name);
void							*find_load_commandseg(char *ptr,
		int nb_loadcmds, unsigned int cmd, char *name);
void							*find_load_commandseg32(char *ptr,
		int nb_loadcmds,
		unsigned int cmd, char *name);
void							lst_add(t_list **begin, void *content,
		int content_size);
void							print_code(char *ptr, uint64_t offset[2],
		unsigned int size, int type);
void							print_name(char *name);
void							long_print2(unsigned long hex, int size);
void							read_32symtab(t_program *prog, char *ptr,
		char *filename);
void							read_lib(t_program *prog, char *ptr,
		char *filename);
unsigned int					uiendian_swap(unsigned int x);
unsigned int					uiendian_read(t_program *prog,
		unsigned int x);
void							sorte_list(t_program *prog, t_list *list);
int								counthex(unsigned long hex);
void							sorte_list_offset(t_program *prog, t_list *list);
void							print_empty(char c, char *s, int size);
void							print_empty2(unsigned long a, char c,
		char *s, int size);
void							oread_lib(t_program *prog, char *ptr,
		char *filename);
void							long_print(unsigned long hex, int size);
t_list							*get_64symtab(t_program *prog, char *ptr,
		char *filename);
t_list							*get_32symtab(t_program *prog, char *ptr,
		char *filename);
char							*construct_name(char *n1, char *n2);
int								not_in_tab(t_list *list, char *name);
char							*get_ptr_header(char *ptr);
int								ismagic(unsigned int c);
int								check_tab(int **tab, int *size, int nb);
unsigned long long				llendian_swap(unsigned long long x);
void							create_seg_list64(t_program *prog,
		struct segment_command_64 *ptr);
int check_ptr(t_program *prog, unsigned int ptr);

#endif

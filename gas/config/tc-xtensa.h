/* tc-xtensa.h -- Header file for tc-xtensa.c.
   Copyright (C) 2003-2022 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#ifndef TC_XTENSA
#define TC_XTENSA 1

struct fix;

#ifndef OBJ_ELF
#error Xtensa support requires ELF object format
#endif

#include "xtensa-isa.h"
#include "xtensa-dynconfig.h"

#define TARGET_BYTES_BIG_ENDIAN 0


/* Maximum number of opcode slots in a VLIW instruction.  */
#define MAX_SLOTS 15


/* For all xtensa relax states except RELAX_DESIRE_ALIGN and
   RELAX_DESIRE_ALIGN_IF_TARGET, the amount a frag might grow is stored
   in the fr_var field.  For the two exceptions, fr_var is a float value
   that records the frequency with which the following instruction is
   executed as a branch target.  The aligner uses this information to
   tell which targets are most important to be aligned.  */

enum xtensa_relax_statesE
{
  RELAX_XTENSA_NONE,

  RELAX_ALIGN_NEXT_OPCODE,
  /* Use the first opcode of the next fragment to determine the
     alignment requirements.  This is ONLY used for LOOPs currently.  */

  RELAX_CHECK_ALIGN_NEXT_OPCODE,
  /* The next non-empty frag contains a loop instruction.  Check to see
     if it is correctly aligned, but do not align it.  */

  RELAX_DESIRE_ALIGN_IF_TARGET,
  /* These are placed in front of labels and converted to either
     RELAX_DESIRE_ALIGN / RELAX_LOOP_END or rs_fill of 0 before
     relaxation begins.  */

  RELAX_ADD_NOP_IF_A0_B_RETW,
  /* These are placed in front of conditional branches.  Before
     relaxation begins, they are turned into either NOPs for branches
     immediately followed by RETW or RETW.N or rs_fills of 0.  This is
     used to avoid a hardware bug in some early versions of the
     processor.  */

  RELAX_ADD_NOP_IF_PRE_LOOP_END,
  /* These are placed after JX instructions.  Before relaxation begins,
     they are turned into either NOPs, if the JX is one instruction
     before a loop end label, or rs_fills of 0.  This is used to avoid a
     hardware interlock issue prior to Xtensa version T1040.  */

  RELAX_ADD_NOP_IF_SHORT_LOOP,
  /* These are placed after LOOP instructions and turned into NOPs when:
     (1) there are less than 3 instructions in the loop; we place 2 of
     these in a row to add up to 2 NOPS in short loops; or (2) the
     instructions in the loop do not include a branch or jump.
     Otherwise they are turned into rs_fills of 0 before relaxation
     begins.  This is used to avoid hardware bug PR3830.  */

  RELAX_ADD_NOP_IF_CLOSE_LOOP_END,
  /* These are placed after LOOP instructions and turned into NOPs if
     there are less than 12 bytes to the end of some other loop's end.
     Otherwise they are turned into rs_fills of 0 before relaxation
     begins.  This is used to avoid hardware bug PR3830.  */

  RELAX_DESIRE_ALIGN,
  /* The next fragment would like its first instruction to NOT cross an
     instruction fetch boundary.  */

  RELAX_MAYBE_DESIRE_ALIGN,
  /* The next fragment might like its first instruction to NOT cross an
     instruction fetch boundary.  These are placed after a branch that
     might be relaxed.  If the branch is relaxed, then this frag will be
     a branch target and this frag will be changed to RELAX_DESIRE_ALIGN
     frag.  */

  RELAX_LOOP_END,
  /* This will be turned into a NOP or NOP.N if the previous instruction
     is expanded to negate a loop.  */

  RELAX_LOOP_END_ADD_NOP,
  /* When the code density option is available, this will generate a
     NOP.N marked RELAX_NARROW.  Otherwise, it will create an rs_fill
     fragment with a NOP in it.  Once a frag has been converted to
     RELAX_LOOP_END_ADD_NOP, it should never be changed back to
     RELAX_LOOP_END.  */

  RELAX_LITERAL,
  /* Another fragment could generate an expansion here but has not yet.  */

  RELAX_LITERAL_NR,
  /* Expansion has been generated by an instruction that generates a
     literal.  However, the stretch has NOT been reported yet in this
     fragment.  */

  RELAX_LITERAL_FINAL,
  /* Expansion has been generated by an instruction that generates a
     literal.  */

  RELAX_LITERAL_POOL_BEGIN,
  RELAX_LITERAL_POOL_END,
  RELAX_LITERAL_POOL_CANDIDATE_BEGIN,
  /* Technically these are not relaxations at all but mark a location
     to store literals later.  Note that fr_var stores the frchain for
     BEGIN frags and fr_var stores now_seg for END frags.  */

  RELAX_NARROW,
  /* The last instruction in this fragment (at->fr_opcode) can be
     freely replaced with a single wider instruction if a future
     alignment desires or needs it.  */

  RELAX_IMMED,
  /* The last instruction in this fragment (at->fr_opcode) contains
     an immediate or symbol.  If the value does not fit, relax the
     opcode using expansions from the relax table.  */

  RELAX_IMMED_STEP1,
  /* The last instruction in this fragment (at->fr_opcode) contains a
     literal.  It has already been expanded 1 step.  */

  RELAX_IMMED_STEP2,
  /* The last instruction in this fragment (at->fr_opcode) contains a
     literal.  It has already been expanded 2 steps.  */

  RELAX_IMMED_STEP3,
  /* The last instruction in this fragment (at->fr_opcode) contains a
     literal.  It has already been expanded 3 steps.  */

  RELAX_SLOTS,
  /* There are instructions within the last VLIW instruction that need
     relaxation.  Find the relaxation based on the slot info in
     xtensa_frag_type.  Relaxations that deal with particular opcodes
     are slot-based (e.g., converting a MOVI to an L32R).  Relaxations
     that deal with entire instructions, such as alignment, are not
     slot-based.  */

  RELAX_FILL_NOP,
  /* This marks the location of a pipeline stall.  We can fill these guys
     in for alignment of any size.  */

  RELAX_UNREACHABLE,
  /* This marks the location as unreachable.  The assembler may widen or
     narrow this area to meet alignment requirements of nearby
     instructions.  */

  RELAX_MAYBE_UNREACHABLE,
  /* This marks the location as possibly unreachable.  These are placed
     after a branch that may be relaxed into a branch and jump. If the
     branch is relaxed, then this frag will be converted to a
     RELAX_UNREACHABLE frag.  */

  RELAX_ORG,
  /* This marks the location as having previously been an rs_org frag.
     rs_org frags are converted to fill-zero frags immediately after
     relaxation.  However, we need to remember where they were so we can
     prevent the linker from changing the size of any frag between the
     section start and the org frag.  */

  RELAX_TRAMPOLINE,
  /* Every few thousand frags, we insert one of these, just in case we may
     need some space for a trampoline (jump to a jump) because the function
     has gotten too big. If not needed, it disappears. */

  RELAX_NONE
};

/* This is used as a stopper to bound the number of steps that
   can be taken.  */
#define RELAX_IMMED_MAXSTEPS (RELAX_IMMED_STEP3 - RELAX_IMMED)

struct xtensa_frag_type
{
  /* Info about the current state of assembly, e.g., transform,
     absolute_literals, etc.  These need to be passed to the backend and
     then to the object file.

     When is_assembly_state_set is false, the frag inherits some of the
     state settings from the previous frag in this segment.  Because it
     is not possible to intercept all fragment closures (frag_more and
     frag_append_1_char can close a frag), we use a pass after initial
     assembly to fill in the assembly states.  */

  unsigned int is_assembly_state_set : 1;
  unsigned int is_no_density : 1;
  unsigned int is_no_transform : 1;
  unsigned int use_longcalls : 1;
  unsigned int use_absolute_literals : 1;

  /* Inhibits relaxation of machine-dependent alignment frags the
     first time through a relaxation....  */
  unsigned int relax_seen : 1;

  /* Information that is needed in the object file and set when known.  */
  unsigned int is_literal : 1;
  unsigned int is_loop_target : 1;
  unsigned int is_branch_target : 1;
  unsigned int is_insn : 1;
  unsigned int is_unreachable : 1;

  unsigned int is_specific_opcode : 1; /* also implies no_transform */

  unsigned int is_align : 1;
  unsigned int is_text_align : 1;
  unsigned int alignment : 5;

  /* A frag with this bit set is the first in a loop that actually
     contains an instruction.  */
  unsigned int is_first_loop_insn : 1;

  /* A frag with this bit set is a branch that we are using to
     align branch targets as if it were a normal narrow instruction.  */
  unsigned int is_aligning_branch : 1;

  /* A trampoline frag that is located in the middle of code and thus
     needs a jump around.  */
  unsigned int needs_jump_around : 1;

  /* For text fragments that can generate literals at relax time, this
     variable points to the frag where the literal will be stored.  For
     literal frags, this variable points to the nearest literal pool
     location frag.  This literal frag will be moved to after this
     location.  For RELAX_LITERAL_POOL_BEGIN frags, this field points
     to the frag immediately before the corresponding RELAX_LITERAL_POOL_END
     frag, to make moving frags for this literal pool efficient.  */
  fragS *literal_frag;

  /* The destination segment for literal frags.  (Note that this is only
     valid after xtensa_move_literals.)  This field is also used for
     LITERAL_POOL_END frags.  */
  segT lit_seg;

  /* Frag chain for LITERAL_POOL_BEGIN frags.  */
  struct frchain *lit_frchain;

  /* For the relaxation scheme, some literal fragments can have their
     expansions modified by an instruction that relaxes.  */
  int text_expansion[MAX_SLOTS];
  int literal_expansion[MAX_SLOTS];
  int unreported_expansion;

  /* For slots that have a free register for relaxation, record that
     register.  */
  expressionS free_reg[MAX_SLOTS];

  /* For text fragments that can generate literals at relax time:  */
  fragS *literal_frags[MAX_SLOTS];
  enum xtensa_relax_statesE slot_subtypes[MAX_SLOTS];
  symbolS *slot_symbols[MAX_SLOTS];
  offsetT slot_offsets[MAX_SLOTS];

  /* For trampoline fragments.  */
  struct fix *jump_around_fix;

  /* When marking frags after this one in the chain as no transform,
     cache the last one in the chain, so that we can skip to the
     end of the chain.  */
  fragS *no_transform_end;
};


/* For VLIW support, we need to know what slot a fixup applies to.  */
typedef struct xtensa_fix_data_struct
{
  int slot;
  symbolS *X_add_symbol;
  offsetT X_add_number;
} xtensa_fix_data;


/* Structure to record xtensa-specific symbol information.  */
typedef struct xtensa_symfield_type
{
  unsigned int is_loop_target : 1;
  unsigned int is_branch_target : 1;
  symbolS *next_expr_symbol;
} xtensa_symfield_type;


/* Structure for saving information about a block of property data
   for frags that have the same flags.   The forward reference is
   in this header file.  The actual definition is in tc-xtensa.c.  */
struct xtensa_block_info_struct;
typedef struct xtensa_block_info_struct xtensa_block_info;


/* Property section types.  */
typedef enum
{
  xt_literal_sec,
  xt_prop_sec,
  max_xt_sec
} xt_section_type;

typedef struct xtensa_segment_info_struct
{
  fragS *literal_pool_loc;
  xtensa_block_info *blocks[max_xt_sec];
} xtensa_segment_info;


extern const char *xtensa_target_format (void);
extern void xtensa_init_fix_data (struct fix *);
extern void xtensa_frag_init (fragS *);
extern int xtensa_force_relocation (struct fix *);
extern int xtensa_validate_fix_sub (struct fix *);
extern void xtensa_frob_label (struct symbol *);
extern void xtensa_md_finish (void);
extern void xtensa_post_relax_hook (void);
extern void xtensa_file_arch_init (bfd *);
extern void xtensa_flush_pending_output (void);
extern bool xtensa_fix_adjustable (struct fix *);
extern void xtensa_symbol_new_hook (symbolS *);
extern long xtensa_relax_frag (fragS *, long, int *);
extern void xtensa_elf_section_change_hook (void);
extern int xtensa_unrecognized_line (int);
extern bool xtensa_check_inside_bundle (void);
extern void xtensa_handle_align (fragS *);
extern char *xtensa_section_rename (const char *);

/* We need to set the target endianness in xtensa_init and not in md_begin.
   This is because xtensa_target_format is called before md_begin, and we
   want to have all non-statically initialized fields initialized.  */

#define HOST_SPECIAL_INIT xtensa_init
extern void xtensa_init (int, char **);

#define TARGET_FORMAT			xtensa_target_format ()
#define TARGET_ARCH			bfd_arch_xtensa
#define TC_SEGMENT_INFO_TYPE		xtensa_segment_info
#define TC_SYMFIELD_TYPE                struct xtensa_symfield_type
#define TC_FIX_TYPE			xtensa_fix_data
#define TC_INIT_FIX_DATA(x)		xtensa_init_fix_data (x)
#define TC_FRAG_TYPE			struct xtensa_frag_type
#define TC_FRAG_INIT(frag, max_bytes)	xtensa_frag_init (frag)
#define TC_FORCE_RELOCATION(fix)	xtensa_force_relocation (fix)
#define TC_FORCE_RELOCATION_SUB_SAME(fix, seg) \
  (GENERIC_FORCE_RELOCATION_SUB_SAME (fix, seg)	\
   || xtensa_force_relocation (fix))
#define	TC_VALIDATE_FIX_SUB(fix, seg)	xtensa_validate_fix_sub (fix)
#define NO_PSEUDO_DOT			xtensa_check_inside_bundle ()
#define tc_canonicalize_symbol_name(s)	xtensa_section_rename (s)
#define tc_canonicalize_section_name(s)	xtensa_section_rename (s)
#define tc_init_after_args()		xtensa_file_arch_init (stdoutput)
#define tc_fix_adjustable(fix)		xtensa_fix_adjustable (fix)
#define tc_frob_label(sym)		xtensa_frob_label (sym)
#define tc_unrecognized_line(ch)	xtensa_unrecognized_line (ch)
#define tc_symbol_new_hook(sym)		xtensa_symbol_new_hook (sym)
#define md_do_align(a,b,c,d,e)		xtensa_flush_pending_output ()
#define md_elf_section_change_hook	xtensa_elf_section_change_hook
#define md_finish			xtensa_md_finish
#define md_flush_pending_output()	xtensa_flush_pending_output ()
#define md_operand(x)
#define TEXT_SECTION_NAME		xtensa_section_rename (".text")
#define DATA_SECTION_NAME		xtensa_section_rename (".data")
#define BSS_SECTION_NAME		xtensa_section_rename (".bss")
#define HANDLE_ALIGN(fragP)		xtensa_handle_align (fragP)
#define MAX_MEM_FOR_RS_ALIGN_CODE	1


/* The renumber_section function must be mapped over all the sections
   after calling xtensa_post_relax_hook.  That function is static in
   write.c so it cannot be called from xtensa_post_relax_hook itself.  */

#define md_post_relax_hook \
  do \
    { \
      int i = 0; \
      xtensa_post_relax_hook (); \
      bfd_map_over_sections (stdoutput, renumber_sections, &i); \
    } \
  while (0)


/* Because xtensa relaxation can insert a new literal into the middle of
   fragment and thus require re-running the relaxation pass on the
   section, we need an explicit flag here.  We explicitly use the name
   "stretched" here to avoid changing the source code in write.c.  */

#define md_relax_frag(segment, fragP, stretch) \
  xtensa_relax_frag (fragP, stretch, &stretched)

/* Only allow call frame debug info optimization when linker relaxation is
   not enabled as otherwise we could generate the DWARF directives without
   the relocs necessary to patch them up.  */
#define md_allow_eh_opt (linkrelax == 0)

#define LOCAL_LABELS_FB 1
#define WORKING_DOT_WORD 1
#define DOUBLESLASH_LINE_COMMENTS
#define TC_HANDLES_FX_DONE
#define TC_FINALIZE_SYMS_BEFORE_SIZE_SEG 0
#define TC_LINKRELAX_FIXUP(SEG) 0
#define MD_APPLY_SYM_VALUE(FIX) 0
#define SUB_SEGMENT_ALIGN(SEG, FRCHAIN) 0

/* Use line number format that is amenable to linker relaxation.  */
#define DWARF2_USE_FIXED_ADVANCE_PC (linkrelax != 0)


/* Resource reservation info functions.  */

/* Returns the number of copies of a particular unit.  */
typedef int (*unit_num_copies_func) (void *, xtensa_funcUnit);

/* Returns the number of units the opcode uses.  */
typedef int (*opcode_num_units_func) (void *, xtensa_opcode);

/* Given an opcode and an index into the opcode's funcUnit list,
   returns the unit used for the index.  */
typedef int (*opcode_funcUnit_use_unit_func) (void *, xtensa_opcode, int);

/* Given an opcode and an index into the opcode's funcUnit list,
   returns the cycle during which the unit is used.  */
typedef int (*opcode_funcUnit_use_stage_func) (void *, xtensa_opcode, int);

/* The above typedefs parameterize the resource_table so that the
   optional scheduler doesn't need its own resource reservation system.

   For simple resource checking, which is all that happens normally,
   the functions will be as follows (with some wrapping to make the
   interface more convenient):

   unit_num_copies_func = xtensa_funcUnit_num_copies
   opcode_num_units_func = xtensa_opcode_num_funcUnit_uses
   opcode_funcUnit_use_unit_func = xtensa_opcode_funcUnit_use->unit
   opcode_funcUnit_use_stage_func = xtensa_opcode_funcUnit_use->stage

   Of course the optional scheduler has its own reservation table
   and functions.  */

int opcode_funcUnit_use_unit (void *, xtensa_opcode, int);
int opcode_funcUnit_use_stage (void *, xtensa_opcode, int);

typedef struct
{
  void *data;
  int cycles;
  int allocated_cycles;
  int num_units;
  unit_num_copies_func unit_num_copies;
  opcode_num_units_func opcode_num_units;
  opcode_funcUnit_use_unit_func opcode_unit_use;
  opcode_funcUnit_use_stage_func opcode_unit_stage;
  unsigned char **units;
} resource_table;

resource_table *new_resource_table
  (void *, int, int, unit_num_copies_func, opcode_num_units_func,
   opcode_funcUnit_use_unit_func, opcode_funcUnit_use_stage_func);
void resize_resource_table (resource_table *, int);
void clear_resource_table (resource_table *);
bool resources_available (resource_table *, xtensa_opcode, int);
void reserve_resources (resource_table *, xtensa_opcode, int);
void release_resources (resource_table *, xtensa_opcode, int);

#endif /* TC_XTENSA */

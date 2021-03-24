#include "../h/opcodes.h"

std::string strings_opcodes [] = {"nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst_2", "iconst_3", "iconst_4", "iconst_5", "lconst_0",
	"lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", "dconst_1", "bipush", "sipush", "ldc", "ldc_w",
	"ldc2_w", "iload", "lload", "fload", "dload", "aload", "iload_0", "iload_1", "iload_2", "iload_3",
	"lload_0", "lload_1", "lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3", "dload_0", "dload_1",
 	"dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", "iaload", "laload", "faload", "daload",
 	"aaload", "baload", "caload", "saload", "istore", "lstore", "fstore", "dstore", "astore", "istore_0",
 	"istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1", "lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2",
 	"fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3", "astore_0", "astore_1", "astore_2", "astore_3", "iastore",
 	"lastore", "fastore", "dastore", "aastore", "bastore", "castore", "sastore", "pop", "pop2", "dup",
 	"dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2", "swap", "iadd", "ladd", "fadd", "dadd",
 	"isub", "lsub", "fsub", "dsub", "imul", "lmul", "fmul", "dmul", "idiv", "ldiv",
	"fdiv", "ddiv", "irem", "lrem", "frem", "drem", "ineg", "lneg", "fneg", "dneg",
	"ishl", "lshl", "ishr", "lshr", "iushr", "lushr", "iand", "land", "ior", "lor",
	"ixor", "lxor", "iinc", "i2l", "i2f", "i2d", "l2i", "l2f", "l2d", "f2i",
	"f2l", "f2d", "d2i", "d2l", "d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl",
	"fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", "iflt", "ifge", "ifgt", "ifle", "if_icmpeq",
	"if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", "if_acmpeq", "if_acmpne", "goto", "jsr", "ret",
	"tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn", "dreturn", "areturn", "return", "getstatic", "putstatic",
	"getfield", "putfield", "invokevirtual", "invokespecial", "invokestatic", "invokeinterface", "invokedynamic", "new", "newarray", "anewarray",
	"arraylength", "athrow", "checkcast", "instanceof", "monitorenter", "monitorexit", "wide", "multianewarray", "ifnull", "ifnonnull",
	"goto_w", "jsr_w", "breakpoint"};

std::map<u1, int> opargs;
void init_opargs() {
	opargs[OP_if_icmpeq] = 2;
	opargs[OP_if_icmpne] = 2;
	opargs[OP_if_icmplt] = 2;
	opargs[OP_if_icmpge] = 2;
	opargs[OP_if_icmpgt] = 2;
	opargs[OP_if_icmple] = 2;
	opargs[OP_if_acmpne] = 2;
	opargs[OP_if_acmpeq] = 2;
	opargs[OP_ldc] = 1;
	opargs[OP_iload] = 1;
	opargs[OP_lload] = 1;
	opargs[OP_fload] = 1;
	opargs[OP_dload] = 1;
	opargs[OP_aload] = 1;
	opargs[OP_istore] = 1;
	opargs[OP_lstore] = 1;
	opargs[OP_fstore] = 1;
	opargs[OP_dstore] = 1;
	opargs[OP_astore] = 1;
	opargs[OP_ret] = 1;
	opargs[OP_bipush] = 1;
	opargs[OP_newarray] = 1;
	opargs[OP_ldc_w] = 2;
	opargs[OP_ldc2_w] = 2;
	opargs[OP_getfield] = 2;
	opargs[OP_putfield] = 2;
	opargs[OP_invokevirtual] = 2;
	opargs[OP_invokespecial] = 2;
	opargs[OP_invokestatic] = 2;
	opargs[OP_new] = 2;
	opargs[OP_anewarray] = 2;
	opargs[OP_checkcast] = 2;
	opargs[OP_instanceof] = 2;
	opargs[OP_iinc] = 2;
	opargs[OP_sipush] = 2;
	opargs[OP_goto] = 2;
	opargs[OP_jsr] = 2;
	opargs[OP_ifnull] = 2;
	opargs[OP_ifnonnull] = 2;
	opargs[OP_ifeq] = 2;
	opargs[OP_ifne] = 2;
	opargs[OP_iflt] = 2;
	opargs[OP_ifge] = 2;
	opargs[OP_ifgt] = 2;
	opargs[OP_ifle] = 2;
	opargs[OP_multianewarray] = 3;
	opargs[OP_invokeinterface] = 4;
	opargs[OP_invokedynamic] = 4;
	opargs[OP_goto_w] = 4;
	opargs[OP_jsr_w] = 4;
	opargs[OP_getstatic] = 2;
	opargs[OP_putstatic] = 2;
};
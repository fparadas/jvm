#include "utils.h"
typedef struct _verification_type_info{
	u1 tag;

	union{

		struct {

			//u1 tag; // possuira valor 0;

		} top_variable_info;

		struct {

			//u1 tag; // possuira valor 1;

		} integer_variable_info;

		struct {

			//u1 tag; // possuira valor 2;

		} float_variable_info;

		/**	 ATENCAo - Tanto para Long como Double (64bits ambas).
		This structure gives the contents of two locations
		in the operand stack or in the local variable array.
		If the location is a local variable, then:
		It must not be the local variable with the highest index.
		The next higher numbered local variable contains the verification type top.
		If the location is an operand stack entry, then:
		The current location must not be the topmost location of the operand stack.
		The next location closer to the top of the operand stack contains the verification type top.
		*/

		struct {

			//u1 tag; // possuira valor 4;

		} long_variable_info;

		struct{

			//u1 tag; // possuira valor 3;

		} double_variable_info;

		struct {

			//u1 tag; // possuira valor 5;

		} null_variable_info;

		struct {

			//u1 tag; // possuira valor 6;

		} uninitializedThis_variable_info;

		/**The Object_variable_info type indicates that the location
		contains an instance of the class represented by the CONSTANT_Class_info*/

		struct {

			//u1 tag; // possuira valor 7;
			u2 cpool_index; // index da classe na constant_pool

		} object_variable_info;

		struct {

			//u1 tag; // possuira valor 8
			u2 offset; /** The offset item indicates the offset, in the code array
						of the Code attribute that contains this StackMapTable
						attribute, of the new instruction (§new) that created the
						object being stored in the location.*/

		} uninitialized_variable_info;

	} type_info;

}VerificationTypeInfo;

typedef struct _stack_map_frame {
	u1 frame_type;
	union{
        /**
         * @brief Same frame.
         *
         * If the frame type is same_frame, it means the frame has exactly
         * the same locals as the previous stack map frame and
         * that the number of stack items is zero. From 0-63.
         */
		struct{
		} same_frame;
        /**
         * @brief same_locals_1_stack_item_frame.
         *
         * If the frame_type is same_locals_1_stack_item_frame,
         * it means the frame has exactly the same
         * locals as the previous stack map frame and that the number
         * of stack items is 1*. From 64-127.
         */
		struct{
			VerificationTypeInfo *stack;

		} same_locals_1_stack_item_frame;
        /**
         * @brief same_locals_1_stack_item_frame_extended.
         *
         * The frame type same_locals_1_stack_item_frame_extended indicates
         * that the frame has exactly the same locals as the previous
         * stack map frame and that the number of stack items is 1.
         * The offset_delta value for the frame is given explicitly.
         * frame_type == 247.
         */
		struct{
			u2 offset_delta;
    	    VerificationTypeInfo *stack;
		} same_locals_1_stack_item_frame_extended;

		struct{

			/**f the frame_type is chop_frame, it means that the operand stack
			is empty and the current locals are the same as the locals in the
			previous frame, except that the k last locals are absent.
			The value of k is given by the formula 251 - frame_type.*/

			//u1 frame_type; //= 248 a 250
			u2 offset_delta;
		} chop_frame;

		struct{

			/**If the frame type is same_frame_extended,
			it means the frame has exactly the same locals as
			the previous stack map frame and that the number of stack items is zero.*/

			//u1 frame_type; // == 251
			u2 offset_delta;

		} same_frame_extended;

		struct{

			/**If the frame_type is append_frame, it means that the
			operand stack is empty and the current locals are the same
			as the locals in the previous frame, except that k
			additional locals are defined. The value of k is given by
			the formula frame_type - 251*/


			//u1 frame_type;// == 252 a 254
			u2 offset_delta;
			VerificationTypeInfo *locals;

		} append_frame;

		struct{
			/**The frame type full_frame is represented by the tag value 255.*/
			//frame_type == 255
        	u2 offset_delta;
        	u2 number_of_locals;
        	VerificationTypeInfo *locals; // Vetor alocar com number_of_locals
        	u2 number_of_stack_items;
        	VerificationTypeInfo *stack; // Vetor alocar com number_of_stack_items
		} full_frame;
	} map_frame_type;
}StackMapFrame;

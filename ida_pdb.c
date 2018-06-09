#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#define USE_ORDER_KORFS
#define PLAN_LEN_MAX 255
//#define FIND_ALL (true)

typedef unsigned char uchar;

#define STATE_WIDTH 5
#define STATE_N (STATE_WIDTH * STATE_WIDTH)

#define DIR_N 4
typedef uchar Direction;
#define dir_reverse(dir) ((Direction)(3 - (dir)))

#ifdef USE_ORDER_KORFS
#define DIR_UP 0
#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_DOWN 3
#else
#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_DOWN 3
#endif

static struct state_tag
{
    uchar tile[STATE_N];
    uchar inv[STATE_N];
    uchar empty;
    uchar h[4], rh[4];
} state;

/* PDB */
static FILE *infile;                              /* pointer to heuristic table file */
#define TABLESIZE 244140625   /* bytes in direct-access database array (25^6) */
static unsigned char h0[TABLESIZE];        /* heuristic tables for pattern databases */
static unsigned char h1[TABLESIZE];
static int whichpat[25] = {0,0,0,1,1,0,0,0,1,1,2,2,0,1,1,2,2,3,3,3,2,2,3,3,3};
static int whichrefpat[25] = {0,0,2,2,2,0,0,2,2,2,0,0,0,3,3,1,1,1,3,3,1,1,1,3,3};
#define inv (state.inv)
/* the position of each tile in order, reflected about the main diagonal */
static int ref[] = {0,5,10,15,20,1,6,11,16,21,2,7,12,17,22,3,8,13,18,23,4,9,14,19,24};
static int rot90[] = {20,15,10,5,0,21,16,11,6,1,22,17,12,7,2,23,18,13,8,3,24,19,14,9,4};
static int rot90ref[] = {20,21,22,23,24,15,16,17,18,19,10,11,12,13,14,5,6,7,8,9,0,1,2,3,4};
static int rot180[] = {24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
static int rot180ref[] = {24,19,14,9,4,23,18,13,8,3,22,17,12,7,2,21,16,11,6,1,20,15,10,5,0};

static void
readfile(unsigned char table[])
{
	int pos[6];                                 /* positions of each pattern tile */
	int index;                                           /* direct access index */

	for (pos[0] = 0; pos[0] < STATE_N; pos[0]++) {
		for (pos[1] = 0; pos[1] < STATE_N; pos[1]++) {
			if (pos[1] == pos[0]) continue;
			for (pos[2] = 0; pos[2] < STATE_N; pos[2]++) {
				if (pos[2] == pos[0] || pos[2] == pos[1]) continue;
				for (pos[3] = 0; pos[3] < STATE_N; pos[3]++) {
					if (pos[3] == pos[0] || pos[3] == pos[1] || pos[3] == pos[2]) continue;
					for (pos[4] = 0; pos[4] < STATE_N; pos[4]++) {
						if (pos[4] == pos[0] || pos[4] == pos[1] || pos[4] == pos[2] || pos[4] == pos[3]) continue;
						for (pos[5] = 0; pos[5] < STATE_N; pos[5]++) {
							if (pos[5] == pos[0] || pos[5] == pos[1] || pos[5] == pos[2] || pos[5] == pos[3] || pos[5] == pos[4])
							continue;
							index = ((((pos[0]*25+pos[1])*25+pos[2])*25+pos[3])*25+pos[4])*25+pos[5];
							table[index] = getc (infile);
						}
					}
				}
			}
		}
	}
}

static void
pdb_load(void)
{
	infile = fopen("pattern_1_2_5_6_7_12", "rb"); /* read 6-tile pattern database */
	readfile (h0);         /* read database and expand into direct-access array */
	fclose(infile);
	printf ("pattern 1 2 5 6 7 12 read in\n");

	infile = fopen("pattern_3_4_8_9_13_14", "rb"); /* read 6-tile pattern database */
	readfile (h1);         /* read database and expand into direct-access array */
	fclose(infile);
	printf ("pattern 3 4 8 9 13 14 read in\n");
}

static unsigned int
hash0(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = ((((inv[1]*STATE_N+inv[2])*STATE_N+inv[5])*STATE_N+inv[6])*STATE_N+inv[7])*STATE_N+inv[12];
	return (h0[hashval]);                       /* total moves for this pattern */
}

static unsigned int
hashref0(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = (((((ref[inv[5]] * STATE_N + ref[inv[10]]) * STATE_N + ref[inv[1]]) * STATE_N +
					ref[inv[6]]) * STATE_N + ref[inv[11]]) * STATE_N + ref[inv[12]]);
	return (h0[hashval]);                       /* total moves for this pattern */
}

static unsigned int
hash1(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = ((((inv[3]*STATE_N+inv[4])*STATE_N+inv[8])*STATE_N+inv[9])*STATE_N+inv[13])*STATE_N+inv[14];
	return (h1[hashval]);                       /* total moves for this pattern */
}

static unsigned int
hashref1(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = (((((ref[inv[15]] * STATE_N + ref[inv[20]]) * STATE_N + ref[inv[16]]) * STATE_N +
					ref[inv[21]]) * STATE_N + ref[inv[17]]) * STATE_N + ref[inv[22]]);
	return (h1[hashval]);                       /* total moves for this pattern */
}

static unsigned int
hash2(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = ((((rot180[inv[21]] * STATE_N + rot180[inv[20]]) * STATE_N + rot180[inv[16]]) * STATE_N +
				rot180[inv[15]]) * STATE_N + rot180[inv[11]]) * STATE_N + rot180[inv[10]];
	return (h1[hashval]);                       /* total moves for this pattern */
}

static unsigned int
hashref2(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = (((((rot180ref[inv[9]] * STATE_N + rot180ref[inv[4]]) * STATE_N + rot180ref[inv[8]]) * STATE_N +
					rot180ref[inv[3]]) * STATE_N + rot180ref[inv[7]]) * STATE_N + rot180ref[inv[2]]);
	return (h1[hashval]);                       /* total moves for this pattern */
}

static unsigned int
hash3(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = ((((rot90[inv[19]] * STATE_N + rot90[inv[24]]) * STATE_N + rot90[inv[18]]) * STATE_N +
				rot90[inv[23]]) * STATE_N + rot90[inv[17]]) * STATE_N + rot90[inv[22]];
	return (h1[hashval]);                       /* total moves for this pattern */
}

static unsigned int
hashref3(void)
{
	int hashval;                                   /* index into heuristic table */
	hashval = (((((rot90ref[inv[23]] * STATE_N + rot90ref[inv[24]]) * STATE_N + rot90ref[inv[18]]) * STATE_N
					+ rot90ref[inv[19]]) * STATE_N + rot90ref[inv[13]]) * STATE_N + rot90ref[inv[14]]);
	return (h1[hashval]);                       /* total moves for this pattern */
}
#undef inv

typedef unsigned int (*HashFunc)(void);
HashFunc hash[] = {hash0, hash1, hash2, hash3},
		 rhash[] = {hashref0, hashref1, hashref2, hashref3};


/* stack implementation */

#define stack_get(i) (stack.buf[(i)])

static struct dir_stack_tag
{
    uchar i;
    uchar buf[PLAN_LEN_MAX];
	uchar old_h[PLAN_LEN_MAX];
	uchar old_rh[PLAN_LEN_MAX];
} stack;

static inline void
stack_put(Direction dir, uchar old_h, uchar old_rh)
{
    stack.buf[stack.i] = dir;
	stack.old_h[stack.i] = old_h;
	stack.old_rh[stack.i] = old_rh;
    ++stack.i;
}
static inline bool
stack_is_empty(void)
{
    return stack.i == 0;
}
static inline void
stack_pop(uchar *dir, uchar *old_h, uchar *old_rh)
{
    --stack.i;
    *dir = stack_get(stack.i);
	*old_h = stack.old_h[stack.i];
	*old_rh = stack.old_rh[stack.i];
}
static inline Direction
stack_peak(void)
{
    return stack_get(stack.i - 1);
}
static void
stack_dump(void)
{
    printf("len=%d: ", stack.i);
    for (int i = 0; i < stack.i; ++i)
        printf("%d ", (int) stack_get(i));
    putchar('\n');
}

/* state implementation */

#define STATE_EMPTY 0
#define POS_X(pos) ((pos) % STATE_WIDTH)
#define POS_Y(pos) ((pos) / STATE_WIDTH)

/*
 * goal: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24]
 */

static int
max(int a, int b)
{
	return a > b ? a : b;
}

#define state_get_h (state.h[0] + state.h[1] + state.h[2] + state.h[3])
#define state_get_rh (state.rh[0] + state.rh[1] + state.rh[2] + state.rh[3])
#define state_calc_h (max(state_get_h, state_get_rh))
#define state_tile_get(i) (state.tile[i])
#define state_tile_set(i, val) (state.tile[(i)] = (val))
#define state_inv_set(i, val) (state.inv[(i)] = (val))

static void state_dump(void);

static inline void
state_init_hvalue(void)
{
	for (int i = 0; i < 4; i++)
	{
		state.h[i] = hash[i]();
		state.rh[i] = rhash[i]();
	}
}

static void
state_tile_fill(const uchar v_list[STATE_N])
{
    for (int i = 0; i < STATE_N; ++i)
    {
        if (v_list[i] == STATE_EMPTY)
            state.empty = i;
        state_tile_set(i, v_list[i]);
        state_inv_set(v_list[i], i);
    }
}

static inline bool
state_is_goal(void)
{
    return state_get_h == 0;
}

static bool movable_table[STATE_N][DIR_N];

static void
init_movable_table(void)
{
    for (int i = 0; i < STATE_N; ++i)
        for (unsigned int d = 0; d < DIR_N; ++d)
        {
            if (d == DIR_RIGHT)
                movable_table[i][d] = (POS_X(i) < STATE_WIDTH - 1);
            else if (d == DIR_LEFT)
                movable_table[i][d] = (POS_X(i) > 0);
            else if (d == DIR_DOWN)
                movable_table[i][d] = (POS_Y(i) < STATE_WIDTH - 1);
            else if (d == DIR_UP)
                movable_table[i][d] = (POS_Y(i) > 0);
        }
}
static inline bool
state_movable(Direction dir)
{
    return movable_table[state.empty][dir];
}

static void
state_dump(void)
{
    printf("%s: g=%d, h=%d, (x,y)=(%u,%u)\n", __func__, stack.i, state_calc_h,
           POS_X(state.empty), POS_Y(state.empty));

    for (int i = 0; i < STATE_N; ++i)
        printf("%d%c", i == state.empty ? 0 : (int) state_tile_get(i),
               POS_X(i) == STATE_WIDTH - 1 ? '\n' : ' ');
    printf("-----------\n");
}

static char assert_direction
    [DIR_UP == 0 && DIR_LEFT == 1 && DIR_RIGHT == 2 && DIR_DOWN == 3 ? 1 : -1];
static int pos_diff_table[DIR_N] = {-STATE_WIDTH, -1, 1, +STATE_WIDTH};

static inline void
state_revert(Direction orig_dir, uchar old_h, uchar old_rh)
{
	int dir = dir_reverse(orig_dir);
    int new_empty = state.empty + pos_diff_table[dir];
    int opponent  = state_tile_get(new_empty);

    state_tile_set(state.empty, opponent);
    state_inv_set(opponent, state.empty);
    state.empty = new_empty;

	int pat = whichpat[opponent],
		rpat = whichrefpat[opponent];

	state.h[pat] = old_h;
	state.rh[rpat] = old_rh;
}

/*
 * solver implementation
 */

static bool
idas_internal(int f_limit, long long *ret_nodes_expanded)
{
    uchar     dir            = 0;
    long long nodes_expanded = 0;
    bool      solved         = false;

	printf("f=%d\n", f_limit);

    for (;;)
    {
        if (state_is_goal())
        {
#if FIND_ALL == true
            solved = true;
#else
            *ret_nodes_expanded = nodes_expanded;
            return true;
#endif
        }

        if ((stack_is_empty() || stack_peak() != dir_reverse(dir)) &&
            state_movable(dir))
        {
			int new_empty = state.empty + pos_diff_table[dir];
			int opponent  = state_tile_get(new_empty);

            ++nodes_expanded;

			state_tile_set(state.empty, opponent);
			state_inv_set(opponent, state.empty);

			int pat = whichpat[opponent];
			int hash_old = state.h[pat];

			state.h[pat] = hash[pat]();

			if (stack.i + 1 + state_get_h <= f_limit)
            {
				int rpat = whichrefpat[opponent];
				int rhash_old = state.rh[rpat];
				HashFunc rh;
				if (pat == 0)
					rh = rpat == 0 ? rhash[0] : rhash[2];
				else if (pat == 1)
					rh = rpat == 2 ? rhash[2] : rhash[3];
				else if (pat == 2)
					rh = rpat == 0 ? rhash[0] : rhash[1];
				else
					rh = rpat == 1 ? rhash[1] : rhash[3];
				state.rh[rpat] = rh();

				if (stack.i + 1 + state_get_rh <= f_limit)
				{
					state.empty = new_empty;
					stack_put(dir, hash_old, rhash_old);
					dir = 0;
					continue;
				}
				else
					state.rh[rpat] = rhash_old;
            }
			else
				state.h[pat] = hash_old;

			state_tile_set(new_empty, opponent);
			state_inv_set(opponent, new_empty);
        }

        while (++dir == DIR_N)
        {
			uchar old_h, old_rh;
            if (stack_is_empty())
            {
                *ret_nodes_expanded = nodes_expanded;
                return solved;
            }

            stack_pop(&dir, &old_h, &old_rh);
            state_revert(dir, old_h, old_rh);
        }
    }
}

void
idas_kernel(uchar *input)
{
    long long nodes_expanded = 0;
    long long total_nodes_expanded = 0;
	int f_limit;

    state_tile_fill(input);
    state_init_hvalue();
	state_dump();
	puts("search start.");

	for (f_limit = state_calc_h;; f_limit += 2)
	{
		nodes_expanded = 0;
		bool found          = idas_internal(f_limit, &nodes_expanded);
		printf("f_limit=%3d, expanded nodes = %lld\n", f_limit, nodes_expanded);
		printf("[Stat:nodes_evaluated]%lld\n", nodes_expanded);
		total_nodes_expanded += nodes_expanded;
		if (found)
			break;
	}
	printf("[Stat:solution_depth]=%d\n", f_limit);
	printf("[Stat:total_nodes_evaluated]%lld\n", total_nodes_expanded);
}

/* host implementation */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define exit_failure(...)                                                      \
    do                                                                         \
    {                                                                          \
        printf(__VA_ARGS__);                                                   \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

static int
pop_int_from_str(const char *str, char **end_ptr)
{
    long int rv = strtol(str, end_ptr, 0);
    errno       = 0;

    if (errno != 0)
        exit_failure("%s: %s cannot be converted into long\n", __func__, str);
    else if (end_ptr && str == *end_ptr)
        exit_failure("%s: reach end of string", __func__);

    return (int) rv;
}

#define MAX_LINE_LEN 100
static void
load_state_from_file(const char *fname, uchar *s)
{
    FILE *fp;
    char  str[MAX_LINE_LEN];
    char *str_ptr = str, *end_ptr;
    int   i;

    fp = fopen(fname, "r");
    if (!fp)
        exit_failure("%s: %s cannot be opened\n", __func__, fname);

    if (!fgets(str, MAX_LINE_LEN, fp))
        exit_failure("%s: fgets failed\n", __func__);

    for (i = 0; i < STATE_N; ++i)
    {
        s[i]    = pop_int_from_str(str_ptr, &end_ptr);
        str_ptr = end_ptr;
    }

    fclose(fp);
}
#undef MAX_LINE_LEN

static void
avoid_unused_static_assertions(void)
{
    (void) assert_direction[0];
}

int
main(int argc, char *argv[])
{
    struct timeval s, e;
	uchar s_list[STATE_N];

	if (argc < 2)
	{
        printf("usage: ./c%d_pdb <ifname>\n", STATE_WIDTH);
		exit(EXIT_FAILURE);
	}

    printf("[Start] STATE_WIDTH = %d, FIND_ALL_SOLUTIONS = %s\n",
			STATE_WIDTH, FIND_ALL ? "true" : "false");

	load_state_from_file(argv[1], s_list);
	init_movable_table();

    gettimeofday(&s, NULL);
	pdb_load();
    gettimeofday(&e, NULL);
    printf("[Timer:pdb_load] %lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

    gettimeofday(&s, NULL);
	idas_kernel(s_list);
    gettimeofday(&e, NULL);
    printf("[Timer:search] %lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

	stack_dump();

	avoid_unused_static_assertions();

	return 0;
}

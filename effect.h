// effect.h

#ifndef	_EFFECT_H_
#define	_EFFECT_H_

// effect numbers

// timed effects
#define	APPEAR_EFFECT		1	// uses EffectTimer
#define	GROW_EFFECT			2	// uses GrowAmount
#define	SHRINK_EFFECT		3	// uses GrowAmount
#define	INVINCIBLE_EFFECT	4	// uses Invincibility
#define	INVISIBLE_EFFECT	5	// uses EffectTimer
#define	PSYCHEDELIC_EFFECT	6	// uses EffectTimer
#define	SLOW_EFFECT			7	// uses EffectTimer2
#define	FAST_EFFECT			8	// uses EffectTimer2
#define	STOP_EFFECT			9	// uses EffectTimer2

// permanent/one-off effects
#define	KEYSWAP_EFFECT		10
#define	HEADSWAP_EFFECT		11
#define	REVERSE_EFFECT		12
#define	SPECKLE_EFFECT		13
#define	TELEPORT_EFFECT		14
#define	DEAD_EFFECT			15
#define	SUPER_EFFECT		16

// glider food!
#define	GLIDER_EFFECT		17

// effect bits

// timed effects
#define	BAPPEAR_EFFECT		(1<<0)
#define	BGROW_EFFECT		(1<<1)
#define	BSHRINK_EFFECT		(1<<2)
#define	BINVINCIBLE_EFFECT	(1<<3)
#define	BINVISIBLE_EFFECT	(1<<4)
#define	BPSYCHEDELIC_EFFECT	(1<<5)
#define	BSLOW_EFFECT		(1<<6)
#define	BFAST_EFFECT		(1<<7)
#define	BSTOP_EFFECT		(1<<8)

// permanent/one-off effects
#define	BKEYSWAP_EFFECT		(1<<9)
#define	BHEADSWAP_EFFECT	(1<<10)
#define	BREVERSE_EFFECT		(1<<11)
#define	BSPECKLE_EFFECT		(1<<12)
#define	BTELEPORT_EFFECT	(1<<13)
#define	BDEAD_EFFECT		(1<<14)
#define	BSUPER_EFFECT		(1<<15)

// effect combinations

#define	LENGTH_EFFECTS		(BGROW_EFFECT|BSHRINK_EFFECT)
#define	SPEED_EFFECTS		(BSLOW_EFFECT|BFAST_EFFECT|BSTOP_EFFECT)
#define	GENERAL_EFFECTS		(BAPPEAR_EFFECT|BINVISIBLE_EFFECT|BPSYCHEDELIC_EFFECT)
#define	PERMANENT_EFFECTS	(BKEYSWAP_EFFECT|BHEADSWAP_EFFECT|BREVERSE_EFFECT|BSPECKLE_EFFECT|BTELEPORT_EFFECT|BDEAD_EFFECT)

// effect functions

void	swap_heads(ULONG s1, ULONG s2);
void	teleport(ULONG s);
void	speckle_tail(ULONG s);
void	reverse(ULONG s);
void	swap_keys(ULONG s);

#endif

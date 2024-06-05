#include "../Include/Offsets.h"

//Offsets::entity_t* Offsets::Ent = reinterpret_cast<Offsets::entity_t*>(OFFSET_ENTITY);

Offsets::gentity_t* GetGentity(int index) {
	return (Offsets::gentity_t*)(OFFSET_GENTITY_BASE + (index * OFFSET_GENTITY_SIZE));
}

Offsets::sCG* GetClient(int index) {
	return (Offsets::sCG*)(OFFSET_CG_BASE + (index * OFFSET_CG_SIZE));
}
Offsets::ScreenSize* Offsets::Screen = reinterpret_cast<Offsets::ScreenSize*>(0x11A65CC);


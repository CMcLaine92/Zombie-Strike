#pragma once
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "Timer.h"
#include <string>

class MovingObject;

class Weapon
{

protected:


	enum Type { PISTOL, SHOTGUN, SMG, ASSUALT_RIFLE, SPECIAL, NONE };
	enum Gun { GLOCK, REVOLVER, SAWN, PUMP, AUTO, MAC10, TECH9, SP90, M16, LIGHT_MG, AK47, SNIPER, FTHROWER, GLAUNCHER };


	SGD::Rectangle m_rRenderRect;

	int category = NONE;
	int type = NONE;
	int currAmmo = 0;
	int magSize = 0;
	int totalAmmo = 0;
	int ammoCapactity = 0;
	int penetratingPower = 0;
	float bulletSpread = 0.0f;
	float recoilTime = 0.0f;
	float reloadTime = 0.0f;
	float damage = 0.0f;
	float speed = 0.0f;
	float lifeTime = 0.0f;
	bool m_bIsAutomatic = false;
	bool m_bIsObtained = false;
	bool m_bIsEquipped = false;
	Timer reloadTimer;
	Timer recoilTimer;
	MovingObject* m_pOwner = nullptr;

	bool reloadB = true;
	bool reloadF = false;
	SGD::HAudio* fire_sound = nullptr;
	SGD::HVoice voice;
	bool reloading = false;




public:
	
	Weapon();

	virtual ~Weapon();

	virtual void Fire(float dt);
	virtual void Update(float dt);
	virtual void ReloadEntire(void);
	virtual void ReloadNeeded(void);

	std::string GetWeaponAnimType(void) const;


	//Accessors
	int GetCurrAmmo() const { return currAmmo; }
	SGD::Rectangle GetRenderRect() { return m_rRenderRect; }
	int GetType(void) const { return category; }
	int GetMagSize(void) const { return magSize; }
	int GetAmmoCap(void) const { return ammoCapactity; }
	int GetPenetratingPower(void) const { return penetratingPower; }
	float GetRecoilTime(void) const { return recoilTime; }
	float GetReloadTime(void) const { return reloadTime; }
	float GetDamage(void) const { return damage; }
	float GetSpeed(void) const { return speed; }
	float GetLifeTime(void) const { return lifeTime; }
	float GetBulletSpread(void) const { return bulletSpread; }
	int GetTotalAmmo(void) const { return totalAmmo; }
	bool GetObtained() { return m_bIsObtained; }
	bool GetAutomatic() { return m_bIsAutomatic; }
	Timer GetReloadTimer(void) const { return reloadTimer; }
	Timer GetRecoilTimer(void) const { return recoilTimer; }
	MovingObject* GetOwner(void) const { return m_pOwner; }
	bool IsReloading() { return reloading; }
	bool GetEquipped() { return m_bIsEquipped; }
	int GetGunType() { return type; }

	//Mutators
	void AddAmmo(int addedAmmo) { totalAmmo += addedAmmo; }
	void SetPenPower(int penPower) { penetratingPower = penPower; }
	void SetTotalAmmo(int tammo) { totalAmmo = tammo; }
	void SetCurrAmmo(int cammo) { currAmmo = cammo; }
	void SetRenderRect(SGD::Rectangle rRect) { m_rRenderRect = rRect; }
	void SetType(int _type)  { category = _type; }
	void SetMagSize(int _magSize)  { magSize = _magSize; }
	void SetAmmoCap(int _ammoCap)  { ammoCapactity = _ammoCap; }
	void SetRecoilTime(float _recoilTime)  { recoilTime = _recoilTime; }
	void SetReloadTime(float _reloadTime)  { reloadTime = _reloadTime; }
	void SetDamage(float _damage)  { damage = _damage; }
	void SetSpeed(float _speed)  { speed = _speed; }
	void SetLifeTime(float _lifeTime)  { lifeTime = _lifeTime; }
	void SetBulletSpread(float _bulletSpread) { bulletSpread = _bulletSpread; }
	void SetOwner(MovingObject* owner);
	void SetAutomatic(bool isAuto) { m_bIsAutomatic = isAuto; }
	void SetObtained(bool isObtained) { m_bIsObtained = isObtained; }
	void SetEquipped(bool isEquipped) { m_bIsEquipped = isEquipped; }
	void SetGunType(int theType) { type = theType; }

};


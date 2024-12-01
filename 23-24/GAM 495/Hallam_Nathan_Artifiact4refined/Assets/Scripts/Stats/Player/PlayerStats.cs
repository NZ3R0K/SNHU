using UnityEngine;

using ILMA.CharacterStats;

[CreateAssetMenu(fileName = "ShuttleStats", menuName = "ScriptableObjects/Stats/Player")]
public class PlayerStats : ScriptableObject
{
	[Header("Movement")]
	[Tooltip("How fast the player is capable of moving")]
	public CharacterStat MaxSpeed = new(0);
	[Tooltip("How fast the player will accelerate")]
	public CharacterStat Acceleration = new(0);
	[Tooltip("How fast the player will rotate")]
	public CharacterStat RotationSpeed = new(0);
	[Tooltip("How long it takes for the player to stop moving when not thrusting. 0 is no stopping.")]
	public CharacterStat BrakingPower = new(0);

	// Recharging - The process of a shield filling broken portions of its array when damaged
	// Regenerate - The process of a shield rebuilding the entire shield array when broken
	[Header("Shields")]
	[Tooltip("The maximum HP the shields have")]
	public CharacterStat ShieldMaxStrength = new(0);
	[Tooltip("How many points does the shields regenerate per second when damaged")]
	public CharacterStat ShieldRechargeRate = new(0);
	[Tooltip("How long in seconds the player has to wait for shields to begin recharge")]
	public CharacterStat ShieldRechargeTimer = new(0);
	[Tooltip("How many points does the shields regenerate per second when broken")]
	public CharacterStat ShieldRegenRate = new(0);
	[Tooltip("How long in seconds it takes for the shields regeneration timer to start after the shields are broken.")]
	public CharacterStat ShieldRegenDelay = new(0);
	[Tooltip("The total time in seconds the player has to wait for shields to begin regenerating from a broken state.")]
	public CharacterStat ShieldRegenTimer = new(0);
	[Tooltip("How many seconds of invulnerability does the player have when their sheilds break")]
	public CharacterStat GracePeriod = new(0);

	public string shuttleName;
	public Sprite shuttleSprite;
	public GameObject shuttlePrefab;
}
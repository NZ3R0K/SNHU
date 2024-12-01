using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class HUDManager : MonoBehaviour
{
	public Image ShieldBar,
		ShieldRecharge;

	public CanvasGroup Shields;

	public Color ShieldNormalColor = new(1f, 1f, 1f, 1f),
		LowShieldBlink1 = new(1f, 0f, 0f, 1f),
		LowShieldBlink2 = new(1f, 0f, 0f, 0.5f);

	public float shieldBlinkInterval1 = 0.25f,
		shieldBlinkInterval2 = 0.25f;

	IEnumerator _shieldBlinkTimer;

	float _currentShieldStrength = 0;

	void UpdateShieldHUD(PlayerController PC)
	{
		float shieldPercentage = _currentShieldStrength / (PC.stats.ShieldMaxStrength.Value * GameSettingsManager.Instance.playerHealthMultiplier);

		ShieldBar.fillAmount = shieldPercentage;

		if (_currentShieldStrength != (PC.stats.ShieldMaxStrength.Value * GameSettingsManager.Instance.playerHealthMultiplier) && Shields.alpha != 1)
			Shields.StopFade(false);

		if (_shieldBlinkTimer == null && _currentShieldStrength < ((PC.stats.ShieldMaxStrength.Value * GameSettingsManager.Instance.playerHealthMultiplier) / 3) && _currentShieldStrength > 0)
		{
			_shieldBlinkTimer = ShieldLowBlink(PC);
			StartCoroutine(_shieldBlinkTimer);
		}
		else if (_shieldBlinkTimer == null && _currentShieldStrength == 0)
		{
			_shieldBlinkTimer = ShieldBrokenBlink(PC);
			StartCoroutine(_shieldBlinkTimer);
		}
	}

	public void SetShieldBar(Component sender, object data)
	{
		sender.TryGetComponent(out PlayerController PC);

		if (!PC)
			return;

		if (PC.gameObject.name != gameObject.transform.root.name)
			return;

		if (data.GetType() != typeof(float))
			return;

		float shieldStrength = (float)data;
		_currentShieldStrength = shieldStrength;
		ShieldBar.fillAmount = _currentShieldStrength;

		UpdateShieldHUD(PC);
	}

	public void SetShieldRecharge(Component sender, object data)
	{
		sender.TryGetComponent(out PlayerController PC);

		if (!PC)
			return;

		if (PC.gameObject.name != gameObject.transform.root.name)
			return;

		if (data.GetType() != typeof(float))
			return;

		float shieldRechargeAmount = (float)data;
		ShieldRecharge.fillAmount = shieldRechargeAmount;
		UpdateShieldHUD(PC);
	}

	public void FadeShields(Component sender, object data)
	{
		sender.TryGetComponent(out PlayerController PC);

		if (!PC)
			return;

		if (PC.gameObject.name != gameObject.transform.root.name)
			return;

		if (data.GetType() != typeof(bool))
			return;

		bool fadeIn = (bool)data;

		Shields.Fade(fadeIn, 1f);
	}

	IEnumerator ShieldLowBlink(PlayerController PC)
	{
		do
		{
			Shields.transform.GetChild(0).GetChild(0).GetComponent<Image>().color = LowShieldBlink1;

			yield return new WaitForSeconds(shieldBlinkInterval1 * 1.5f);

			Shields.transform.GetChild(0).GetChild(0).GetComponent<Image>().color = ShieldNormalColor;
			Shields.transform.GetChild(1).GetChild(0).GetComponent<Image>().color = ShieldNormalColor;

			yield return new WaitForSeconds(shieldBlinkInterval2 * 1.5f);
		}
		while (_currentShieldStrength < ((PC.stats.ShieldMaxStrength.Value * GameSettingsManager.Instance.playerHealthMultiplier) / 3) && _currentShieldStrength > 0);

		//If the current shield strength is not broken, set color back to normal, else set it to the broken color
		if (_currentShieldStrength != 0)
		{
			Shields.transform.GetChild(0).GetChild(0).GetComponent<Image>().color = ShieldNormalColor;
			Shields.transform.GetChild(1).GetChild(0).GetComponent<Image>().color = ShieldNormalColor;
		}
		else if (_currentShieldStrength <= 0)
		{
			Shields.transform.GetChild(0).GetChild(0).GetComponent<Image>().color = LowShieldBlink1;
			Shields.transform.GetChild(1).GetChild(0).GetComponent<Image>().color = LowShieldBlink1;
		}

		_shieldBlinkTimer = null;
		UpdateShieldHUD(PC);
	}

	IEnumerator ShieldBrokenBlink(PlayerController PC)
	{
		do
		{
			Shields.transform.GetChild(0).GetChild(0).GetComponent<Image>().color = LowShieldBlink1;
			Shields.transform.GetChild(1).GetChild(0).GetComponent<Image>().color = LowShieldBlink1;

			yield return new WaitForSeconds(shieldBlinkInterval1);

			Shields.transform.GetChild(0).GetChild(0).GetComponent<Image>().color = LowShieldBlink2;
			Shields.transform.GetChild(1).GetChild(0).GetComponent<Image>().color = LowShieldBlink2;

			yield return new WaitForSeconds(shieldBlinkInterval2);
		}
		while (_currentShieldStrength <= 0);

		Shields.transform.GetChild(0).GetChild(0).GetComponent<Image>().color = ShieldNormalColor;
		Shields.transform.GetChild(1).GetChild(0).GetComponent<Image>().color = ShieldNormalColor;

		_shieldBlinkTimer = null;
		UpdateShieldHUD(PC);
	}
}

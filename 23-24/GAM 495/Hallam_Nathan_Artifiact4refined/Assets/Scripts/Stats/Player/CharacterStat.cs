using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace ILMA.CharacterStats
{
	[Serializable]
	public class CharacterStat
	{
		/// <summary>
		/// The starting value for the stat.
		/// </summary>
		public float BaseValue;

		/// <summary>
		/// The base value with all the modifications applied.
		/// </summary>
		public virtual float Value
		{
			get
			{
				if (isDirty || BaseValue != lastBaseValue)
				{
					lastBaseValue = BaseValue;
					_value = CalculateFinalValue();
					isDirty = false;
				}
				return _value;
			}
		}

		/// <summary>
		/// Does the value need an update or not.
		/// </summary>
		protected bool isDirty = true;
		protected float _value;

		/// <summary>
		/// Storage for BaseValue to determine if the base state was modified and thus needs an update.
		/// </summary>
		protected float lastBaseValue = float.MinValue;

		protected readonly List<StatModifier> statModifiers;
		public readonly ReadOnlyCollection<StatModifier> StatModifiers;

		public CharacterStat()
		{
			statModifiers = new List<StatModifier>();

			StatModifiers = statModifiers.AsReadOnly();
		}

		public CharacterStat(float baseValue) : this()
		{
			BaseValue = baseValue;
		}

		public virtual void AddModifier(StatModifier modifier)
		{
			isDirty = true;
			statModifiers.Add(modifier);
			statModifiers.Sort(CompareModifierOrder);
		}

		protected virtual int CompareModifierOrder(StatModifier a, StatModifier b)
		{
			if (a.Order < b.Order)
			{
				return -1;
			}
			else if (a.Order > b.Order)
			{
				return 1;
			}
			return 0;
		}

		public virtual bool RemoveModifier(StatModifier modifier)
		{

			if (statModifiers.Remove(modifier))
			{
				isDirty = true;
				return true;
			}

			return false;
		}

		public virtual bool RemoveAllModifiersFromSource(object source)
		{
			bool didRemove = false;

			for (int i = statModifiers.Count - 1; i >= 0; i--)
			{
				if (statModifiers[i].Source == source)
				{
					isDirty = true;
					didRemove = true;
					statModifiers.RemoveAt(i);
				}
			}

			return didRemove;
		}

		protected virtual float CalculateFinalValue()
		{
			float finalValue = BaseValue;
			float sumPercentAdd = 0;

			for (int i = 0; i < statModifiers.Count; i++)
			{
				StatModifier mod = statModifiers[i];

				if (mod.Type == StatModType.Flat)
				{
					finalValue += mod.Value;
				}
				else if (mod.Type == StatModType.PercentAdd)
				{
					sumPercentAdd += mod.Value;

					if (i + 1 >= statModifiers.Count || statModifiers[i + 1].Type != StatModType.PercentAdd)
					{
						finalValue *= 1 + sumPercentAdd;
						sumPercentAdd = 0;
					}
				}
				else if (mod.Type == StatModType.PercentMultiply)
				{
					finalValue *= 1 + mod.Value;
				}
				else if (mod.Type == StatModType.Override)
				{
					finalValue = mod.Value;
				}

			}

			return (float)Math.Round(finalValue, 4);
		}
	}
}